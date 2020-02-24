#pragma once
#include <cstddef>
#include <array>

namespace gloomy::src {
	struct BufferView final {
		const std::byte* data = nullptr;
		size_t size = 0;

		template<typename T>
		inline static BufferView from(const T& container) { 
			return BufferView{
				.data = reinterpret_cast<const std::byte*>(container.data()),
				.size = container.size() * sizeof(typename T::value_type)
			};
		}
	};
}