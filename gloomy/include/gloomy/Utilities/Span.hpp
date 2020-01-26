#pragma once
#include <cstddef>
#include <vector>
#include <nonstd/span.hpp>

namespace gloomy::util {
	template<typename T>
	using MutableSpan = nonstd::span<T>;

	template<typename T>
	using Span = nonstd::span<const T>;
	
	using MutableByteSpan = MutableSpan<std::byte>;
	using ByteSpan = Span<std::byte>;

	template<typename T>
	MutableByteSpan as_mutable_byte_span(T& container) {
		return MutableByteSpan(reinterpret_cast<std::byte*>(container.data()), sizeof(typename T::value_type)* container.size());
	};

	template<typename T>
	ByteSpan as_byte_span(const T& container) {
		return ByteSpan(const_cast<std::byte*>(reinterpret_cast<const std::byte*>(container.data())), sizeof(typename T::value_type)* container.size());
	};
}