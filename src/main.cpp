#include "asmjit/core/jitallocator.h"
#include "luna/Eval/Require.hpp"
#include "luna/Eval/Val.hpp"
#include "luna/Eval/Eval.hpp"
#include "luna/Jit.hpp"
#include "luna/Parse/Ast.hpp"

#include <filesystem>
#include <immer/map.hpp>
#include <immer/map_transient.hpp>
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <cstring>

#include <asmjit/core.h>

// typedef int (*Inc_Func_Ptr)(int);

// int main() {
// 	// clang-format off
// 	std::vector<uint8_t> win_x64_add1_bin = {
// 		0x8d, 0x41, 0x01,  // lea eax, [rcx + 1]
// 		0xc3   // ret
// 	};
// 	// clang-format on

// 	auto fn		= luna::jit_fn<int(int)>(win_x64_add1_bin);
// 	auto result = fn(99);

// 	std::cout << "========= AsmJit test =========" << std::endl;
// 	std::cout << "input: 99 -> output: " << result << std::endl;  // 输出 100

// 	return 0;
// }

#include <asmjit/x86.h>
using namespace asmjit;

// 定义我们要动态生成的 JIT 函数原型
// 该函数在运行期不接受宿主的任何特殊参数，完全靠自己搞定一切
typedef void (*JitEntryFunc)(const char* libPath);

int main() {
	// 1. 初始化 AsmJit 运行时与汇编器
	JitRuntime rt;
	CodeHolder code;
	code.init(rt.environment());
	x86::Assembler a(&code);

	// =====================================================================
	// 步骤一：利用 PEB 链表，合法获取 kernel32.dll 的基地址
	// =====================================================================
	// 传参约定：Windows x64 下第一个参数在 RCX (传入要加载的 DLL 路径字符串指针)
	// 我们先把这个珍贵的路径指针存入 R15 寄存器备用
	a.mov(x86::r15, x86::rcx);

	// 开始摸 PEB 链表
	// 【修正处】：直接用 x86::gs(0x60) 读取 64位 TIB 里的 PEB 指针
	auto g = x86::qword_ptr(0x60);
	g.setSegment(x86::gs);
	a.mov(x86::rax, g);
	a.mov(x86::rax, x86::ptr(x86::rax, 0x18));	// rax = PEB->Ldr
	a.mov(x86::rsi, x86::ptr(x86::rax, 0x30));	// rsi = InInitializationOrderModuleList (ntdll)

	// 顺着模块链表断链往后找
	a.mov(x86::rsi, x86::ptr(x86::rsi));		// 走到下一个模块 (通常是 kernelbase.dll)
	a.mov(x86::rsi, x86::ptr(x86::rsi));		// 再走到下一个模块 (kernel32.dll)
	a.mov(x86::r13, x86::ptr(x86::rsi, 0x10));	// r13 = kernel32.dll 的绝对内存基地址！

	// =====================================================================
	// 步骤二：手撕 kernel32.dll 的 PE 导出表，寻找 "LoadLibraryA"
	// =====================================================================
	// 顺着 r13 (基地址) 找 PE 头
	a.mov(x86::ebx, x86::ptr(x86::r13, 0x3C));	// ebx = e_lfanew (PE 签名偏移)
	a.add(x86::rbx, x86::r13);					// rbx = PE Header 绝对地址

	// 读出数据目录区（Data Directory）的导出表 RVA (偏移是 0x88)
	a.mov(x86::edx, x86::ptr(x86::rbx, 0x88));	// edx = Export Table RVA
	a.add(x86::rdx, x86::r13);					// rdx = Export Table 绝对地址

	// 读出名称指针数组的 RVA (AddressOfNames, 偏移是 0x20)
	a.mov(x86::edi, x86::ptr(x86::rdx, 0x20));	// edi = AddressOfNames RVA
	a.add(x86::rdi, x86::r13);					// rdi = AddressOfNames 绝对指针数组

	// 读出导出函数总数 (NumberOfNames, 偏移是 0x18)
	a.mov(x86::ecx, x86::ptr(x86::rdx, 0x18));	// ecx = 循环计数器 (函数总数)
	a.xor_(x86::r12, x86::r12);					// r12 作为当前遍历的 index = 0

	// ---------------------------------------------------------------------
	// 字符串匹配循环（微型 strcmp）
	// 为了让代码保持极简，我们直接看函数名的前 4 个字节是不是 "Load"
	// ---------------------------------------------------------------------
	Label L_Loop  = a.newLabel();
	Label L_Found = a.newLabel();

	a.bind(L_Loop);
	a.jecxz(L_Found);  // 如果找完了还没找到就跳出

	// 读出当前 index 的函数名字符串 RVA
	// 使用 rdi + r12 * 4 寻址（由于 AddressOfNames 是 32位 RVA 数组，每个元素占 4 字节）
	a.mov(x86::r8d, x86::ptr(x86::rdi, x86::r12, 2, 0));  // scale=2 代表乘以 4
	a.add(x86::r8, x86::r13);							  // r8 = 当前函数名字符串的绝对地址

	// 绝杀匹配：直接看前 4 个字节是不是 "Load" (即小端序的 0x64616F4C)
	a.cmp(x86::dword_ptr(x86::r8), 0x64616F4C);
	a.je(L_Found);	  // 匹配成功，去算地址

	a.inc(x86::r12);  // index++
	a.loop(L_Loop);	  // ecx--, 继续循环

	// ---------------------------------------------------------------------
	// 找到 "LoadLibraryA" 后的地址计算
	// ---------------------------------------------------------------------
	a.bind(L_Found);
	// 读出 Ordinal 数组 RVA (AddressOfNameOrdinals, 偏移是 0x24)
	a.mov(x86::eax, x86::ptr(x86::rdx, 0x24));
	a.add(x86::rax, x86::r13);	// rax = Ordinal 数组绝对地址
	// Ordinal 数组每个元素是 16位 (word)，所以 scale=1 代表乘以 2
	a.movzx(x86::r9d, x86::word_ptr(x86::rax, x86::r12, 1));

	// 读出函数地址数组 RVA (AddressOfFunctions, 偏移是 0x1c)
	a.mov(x86::eax, x86::ptr(x86::rdx, 0x1C));
	a.add(x86::rax, x86::r13);	// rax = AddressOfFunctions 绝对地址
	// AddressOfFunctions 数组元素是 32位 (dword)，所以 scale=2 代表乘以 4
	a.mov(x86::r14d, x86::ptr(x86::rax, x86::r9, 2));
	a.add(x86::r14, x86::r13);	// r14 = LoadLibraryA 的绝对内存指针！！！

	// =====================================================================
	// 步骤三：调用白嫖到的 LoadLibraryA 加载外部动态库
	// =====================================================================
	// 按照 Win64 ABI 规范，调用前平衡影子栈（Shadow Space）
	a.sub(x86::rsp, 40);

	a.mov(x86::rcx, x86::r15);	// 将最开始存好的 DLL 路径传递给第一参数 RCX
	a.call(x86::r14);			// 绝杀：直接调用 LoadLibraryA！

	a.add(x86::rsp, 40);		// 恢复栈平衡
	a.ret();					// 执行流返回宿主

	// =====================================================================
	// 4. 将生成的机器码绑定到 JIT 可执行内存页中
	// =====================================================================
	JitEntryFunc runJitCode;
	Error		 err = rt.add(&runJitCode, &code);
	if (err) {
		std::cerr << "AsmJit 编译失败!" << std::endl;
		return 1;
	}

	std::cout << "[host] JIT bin ready" << std::endl;
	std::cout << "[host] calling JIT bin" << std::endl;

	// =====================================================================
	// 5. 宿主闭眼 Call 运行（触发自举）
	// =====================================================================
	// 加载系统自带的 user32.dll，如果成功，说明 JIT 内部完全独立把库拉起来了
	runJitCode("user32.dll");

	std::cout << "[host] JIT success!" << std::endl;

	// 清理 JIT 内存
	rt.release(runJitCode);
	return 0;
}