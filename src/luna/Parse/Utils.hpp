#pragma once

#include "pars.hpp"

namespace luna::Parse {
template<typename... RequiresQueryTs, typename FnT>
inline constexpr auto with_effect(FnT&& fn) -> decltype(auto) {
	return pars::with_effect<pars::required_query_t(RequiresQueryTs...)>(std::forward<FnT>(fn));
}

}  // namespace luna::Parse