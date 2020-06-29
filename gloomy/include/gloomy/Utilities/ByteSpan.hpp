#pragma once
#include <span>
#include <cstdint>

namespace gloomy::util {
    template<typename T>
    inline std::span<const std::byte> as_bytes(const T* ptr, std::size_t size) {
        return std::span<const std::byte>(reinterpret_cast<const std::byte*>(ptr), size * sizeof(T));
    }
}
