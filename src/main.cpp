#include "luna/Lexer.hpp"
#include "luna/String.hpp"

#include <spdlog/spdlog.h>

#include <iostream>

using namespace luna::lex;
using namespace luna;
using std::operator""sv;

int main() {
	auto script =
		// 		u8R"(
		// local { :print } = require "io"
		// local a =
		// 	a: b
		// 	c: hello.s
		// )";

		u8R"(
"\"hello!\""
'world!\\'
[[what?!
	[[this is
	[[fucking multiline??!!]]
)";

	const auto ts = tokenize(script);
	std::cout << ts;
}

// int main(int argc, char** argv) {
// 	using namespace luna;

// 	const auto script =
// 		R"(local a = 1
// 	local b = match a
// 		1: "sa"
// 		2: "bi"
// 	)";

// 	const auto ts = lex(script).value();

// 	// constexpr auto trie = Trie<Keyword> { {} };

// 	for (const auto& t : ts) std::cout << to_string(t) << " ";
// }
