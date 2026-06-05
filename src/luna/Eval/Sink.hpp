#pragma once

#include "luna/Eval/Val.hpp"

#include <iterator>

namespace luna::Eval {
inline auto sink(const Tbl& tbl, std::output_iterator<std::byte> auto&& out) -> void {}

}  // namespace luna::Eval