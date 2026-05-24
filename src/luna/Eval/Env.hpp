#pragma once

#include <absl/container/flat_hash_map.h>

namespace luna::Eval {
struct Env : absl::flat_hash_map<struct Val*, struct Val*> {};
}  // namespace luna::Eval
