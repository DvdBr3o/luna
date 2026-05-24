#pragma once

namespace luna {
template<typename T>
concept EmitterC = requires(T emitter) { emitter.emit(); };
}  // namespace luna
