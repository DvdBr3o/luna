#pragma once

#include <absl/container/flat_hash_map.h>

namespace luna::Eval {
struct Env : absl::flat_hash_map<struct Val*, struct Val*> {
	struct ScopedUpdateGuard {
		using Entry = std::pair<struct Val*, struct Val*>;

		Env&			   env;
		std::vector<Entry> origins;

		~ScopedUpdateGuard() {
			for (const auto& [k, v] : origins) env[k] = v;
		}
	};

	auto scoped_update(std::span<const std::pair<struct Val*, struct Val*>> updates)
		-> ScopedUpdateGuard {
		ScopedUpdateGuard guard {*this};

		guard.origins.reserve(updates.size());
		for (const auto& [k, v] : updates) {
			guard.origins.emplace_back(k, this->at(k));
			(*this)[k] = v;
		}

		return guard;
	}
};

class ChainedEnv : public Env {
public:
	ChainedEnv(const ChainedEnv* parent_env) : _parent_env(parent_env) {}

private:
	const ChainedEnv* _parent_env = nullptr;
};
}  // namespace luna::Eval
