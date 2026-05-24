#pragma once

#include <memory>

namespace luna {
template<typename T>
class OwnPtr : public std::unique_ptr<T> {
public:
	using std::unique_ptr<T>::unique_ptr;

	OwnPtr(const OwnPtr& another) : std::unique_ptr<T> {std::make_unique<T>(*another)} {}

	auto& operator=(const OwnPtr& another) {
		if (this != another)
			*this = std::make_unique<T>(*another);
	}
};
}  // namespace luna