#pragma once

#include "luna/IndexSpan.hpp"

#include <utf8/cpp20.h>
#include <spdlog/spdlog.h>

#include <string>
#include <string_view>
#include <utility>
#include <iostream>

namespace luna {
	using Char32	  = utf8::utfchar32_t;
	using U8CodePoint = Char32;
	class U8String;
	class U8StringView;

	class U8String : public std::u8string {
	public:
		using iterator		 = decltype(utf8::iterator(
			  std::declval<std::u8string::iterator>(),
			  std::declval<std::u8string::iterator>(),
			  std::declval<std::u8string::iterator>()
		  ));
		using const_iterator = const iterator;
		using Char			 = decltype(*std::declval<iterator>());

	public:
		using std::u8string::u8string;

	public:
		auto begin() -> iterator {
			return utf8::iterator(
				this->std::u8string::begin(),
				this->std::u8string::begin(),
				this->std::u8string::end()
			);
		}

		auto end() -> iterator {
			return utf8::iterator(
				this->std::u8string::end(),
				this->std::u8string::begin(),
				this->std::u8string::end()
			);
		}

		auto			   operator[](IndexSpan span) -> U8StringView;

		explicit		   operator std::string() { return reinterpret_cast<std::string&>(*this); }

		[[nodiscard]] auto view() const -> U8StringView;
	};

	class U8StringView : public std::u8string_view {
	public:
		using iterator		 = decltype(utf8::iterator(
			  std::declval<std::u8string_view::iterator>(),
			  std::declval<std::u8string_view::iterator>(),
			  std::declval<std::u8string_view::iterator>()
		  ));
		using const_iterator = const iterator;
		using Char			 = decltype(*std::declval<iterator>());

	public:
		using std::u8string_view::u8string_view;

		U8StringView(std::u8string_view sv) : std::u8string_view(sv) {}

		U8StringView(iterator begin, iterator end) : std::u8string_view(begin.base(), end.base()) {}

	public:
		[[nodiscard]] auto begin() -> iterator {
			return utf8::iterator(
				this->std::u8string_view::begin(),
				this->std::u8string_view::begin(),
				this->std::u8string_view::end()
			);
		}

		[[nodiscard]] auto begin() const -> const iterator {
			return utf8::iterator(
				this->std::u8string_view::begin(),
				this->std::u8string_view::begin(),
				this->std::u8string_view::end()
			);
		}

		[[nodiscard]] auto end() -> iterator {
			return utf8::iterator(
				this->std::u8string_view::end(),
				this->std::u8string_view::begin(),
				this->std::u8string_view::end()
			);
		}

		[[nodiscard]] auto end() const -> const iterator {
			return utf8::iterator(
				this->std::u8string_view::end(),
				this->std::u8string_view::begin(),
				this->std::u8string_view::end()
			);
		}

		[[nodiscard]] auto first(std::size_t n = 0) const -> Char {
			auto it = begin();
			while (n--) ++it;
			return *it;
		}

		[[nodiscard]] auto iter_first(std::size_t n = 0) const -> iterator {
			auto it = begin();
			while (it != end() && n--) ++it;
			return it;
		}

		[[nodiscard]] auto try_iter_first(std::size_t n = 0) const -> std::optional<iterator> {
			auto it = begin();
			while (it != end() && n--) ++it;
			if (it != end())
				return it;
			else
				return std::nullopt;
		}

		auto operator[](std::size_t n) const -> Char { return first(n); }

		auto operator[](IndexSpan span) const -> U8StringView {
			return U8StringView { this->substr(span.start, span.len) };
		}

		friend auto& operator<<(std::ostream& os, const U8StringView& self) {
			os << static_cast<std::string_view>(self);
			return os;
		}

		explicit operator std::string_view() const {
			return { reinterpret_cast<const char*>(data()), size() };  // FIXME: overhead?
		}

		explicit operator std::string_view() { return reinterpret_cast<std::string_view&>(*this); }
	};

	auto U8String::view() const -> U8StringView {
		return U8StringView { *this };
	}

	inline static auto
		operator-(const U8StringView::iterator& lhs, const U8StringView::iterator& rhs) {
		return rhs.base() - lhs.base();
	}

	class U8Cursor : public U8StringView {
	public:
		using U8StringView::U8StringView;

		inline static constexpr Char eof = 0;

	public:
		auto bump() -> Char {
			if (_cursor == end())
				return eof;
			else
				return _prev = *(_cursor++);
		}

		[[nodiscard]] auto first(std::size_t n = 0) const -> Char {
			auto cursor = _cursor;
			while (n--) ++cursor;
			return *cursor;
		}

		[[nodiscard]] auto prev() const -> Char { return _prev; }

		[[nodiscard]] auto ended() const -> bool { return _cursor == end(); }

		[[nodiscard]] auto iter() const -> iterator { return _cursor; }

		inline friend auto operator-(const U8Cursor& lhs, const U8StringView::iterator& rhs) {
			return rhs - static_cast<const U8StringView::iterator&>(lhs._cursor);
		}

		inline friend auto operator-(const U8StringView::iterator& lhs, const U8Cursor& rhs) {
			return static_cast<const U8StringView::iterator&>(rhs._cursor) - lhs;
		}

	private:
		iterator _cursor = begin();
		Char	 _prev;
	};

}  // namespace luna

template<>
struct fmt::formatter<luna::U8StringView> {
	inline constexpr static auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const luna::U8StringView& self, FormatContext& ctx) -> decltype(ctx.out()) {
		return fmt::format_to(ctx.out(), "{}", static_cast<std::string_view>(self));
	}
};

template<>
struct std::formatter<luna::U8StringView> {
	inline constexpr static auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

	auto format(const luna::U8StringView& self, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "{}", static_cast<std::string_view>(self));
	}
};

namespace luna::u8 {
	using String	 = luna::U8String;
	using StringView = luna::U8StringView;
	using Char32	 = luna::Char32;
	using CodePoint	 = luna::U8CodePoint;
	using Cursor	 = luna::U8Cursor;
}  // namespace luna::u8
