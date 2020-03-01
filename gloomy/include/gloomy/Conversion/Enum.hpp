#pragma once
#include <type_traits>

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>

namespace gloomy {
	template<typename E>
	constexpr Enum from_enum(E value) { return static_cast<typename std::underlying_type_t<E>>(value); }

	template<typename E>
	constexpr E to_enum(Enum value) { return static_cast<E>(value); }

	template<typename E1, typename E2>
	constexpr E1 as_enum(E2 value) { return to_enum<E1>(from_enum(value)); }
}