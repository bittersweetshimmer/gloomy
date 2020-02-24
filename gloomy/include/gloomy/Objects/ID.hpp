#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Utilities/Distinct.hpp>

namespace gloomy {
	using RawID = U32;
	constexpr RawID null_raw_id = 0;

	template<typename T>
	struct ID : util::Distinct<RawID, T> {
		ID() : util::Distinct<RawID, T>(null_raw_id) {};
		ID(RawID raw) : util::Distinct<RawID, T>(raw) {};

		constexpr auto is_valid() const -> bool { return this->get() != null_raw_id; }
		constexpr auto is_null() const -> bool { return !this->is_valid(); }
	};

	template<typename T>
	ID<T> null_id() { return ID<T>(null_raw_id); }
}