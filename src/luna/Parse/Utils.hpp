#pragma once

#include "pars/Legacy.hpp"

namespace luna::Parse {
template<typename... RequiresQueryTs, typename FnT>
inline constexpr auto with_effect(FnT&& fn) -> decltype(auto) {
	return pars::Legacy::with_effect<pars::Legacy::required_query_t(RequiresQueryTs...)>(
		std::forward<FnT>(fn)
	);
}

}  // namespace luna::Parse