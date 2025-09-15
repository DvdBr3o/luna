#include "luna/Lexer.hpp"
#include "luna/String.hpp"

#include <spdlog/spdlog.h>

#include <iostream>

using namespace luna::lex;
using namespace luna;
using std::operator""sv;

int main() {
	auto script =
		u8R"(
local { :print } = require "io"
local a =
	a: b
	c: hello.s
	f: true or false
)";

	const auto ts = tokenize(script);
	std::cout << ts;
}