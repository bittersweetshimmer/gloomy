#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class IndexType : gloomy::Enum {
        U8 = gl::raw::UNSIGNED_BYTE,
        U16 = gl::raw::UNSIGNED_SHORT,
        U32 = gl::raw::UNSIGNED_INT
    };

    template<typename T>
    constexpr IndexType index_type() = delete;

    template<> constexpr IndexType index_type<U8>() { return IndexType::U8; }
    template<> constexpr IndexType index_type<U16>() { return IndexType::U16; }
    template<> constexpr IndexType index_type<U32>() { return IndexType::U32; }

    namespace priv {
        template<IndexType T>
        struct from_index_type;

        template<> struct from_index_type<IndexType::U8> { using type = U8; };
        template<> struct from_index_type<IndexType::U16> { using type = U16; };
        template<> struct from_index_type<IndexType::U32> { using type = U32; };
    }

    template<IndexType T>
    using from_index_type = typename priv::from_index_type<T>::type;
}
