#pragma once

#include <asmjit/core.h>
#include <asmjit/core/jitallocator.h>

#include <span>

namespace luna {
class JitMemAllocator : asmjit::JitAllocator {
public:
	template<typename FnSigT>
	class JitFn : asmjit::JitAllocator::Span {
	public:
		constexpr JitFn(void* rx, void* rw) : asmjit::JitAllocator::Span(rx, rw) {}

		constexpr JitFn(std::span<const std::byte> data) {
			JitMemAllocator::get().alloc(*this, data.size());
			std::memcpy(rx(), data.data(), data.size_bytes());
			asmjit::VirtMem::flushInstructionCache(rx(), data.size_bytes());
		}

		constexpr ~JitFn() { JitMemAllocator::get().release(_rx); }

		template<typename... Args>
		constexpr auto operator()(Args&&... args) -> decltype(auto) {
			return reinterpret_cast<std::add_pointer_t<FnSigT>>(rx())(std::forward<Args>(args)...);
		}
	};

public:
	inline static auto get() -> JitMemAllocator& {
		static JitMemAllocator allocator;
		return allocator;
	}

	template<typename FnSigT>
	auto fn(std::span<const std::byte> s) -> JitFn<FnSigT> {
		return {s};
	}

	template<typename FnSigT>
	auto fn(std::span<std::uint8_t> s) -> JitFn<FnSigT> {
		return {
			std::span<const std::byte> {reinterpret_cast<const std::byte*>(s.data()), s.size()}
		};
	}

private:
	using asmjit::JitAllocator::JitAllocator;
	JitMemAllocator() = default;
};

inline auto jit_mem_allocator() -> JitMemAllocator& {
	return JitMemAllocator::get();
}

template<typename FnSigT>
auto jit_fn(std::span<const std::byte> s) -> JitMemAllocator::JitFn<FnSigT> {
	return jit_mem_allocator().fn<FnSigT>(s);
}

template<typename FnSigT>
auto jit_fn(std::span<std::uint8_t> s) -> JitMemAllocator::JitFn<FnSigT> {
	return jit_mem_allocator().fn<FnSigT>(s);
}

}  // namespace luna