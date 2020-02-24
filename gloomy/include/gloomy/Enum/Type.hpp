#pragma once
#include <cstdint>
#include <type_traits>

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class Type : Enum {
        FLOAT = gl::raw::FLOAT,
        I8 = gl::raw::BYTE,
        U8 = gl::raw::UNSIGNED_BYTE,
        I16 = gl::raw::SHORT,
        U16 = gl::raw::UNSIGNED_SHORT,
        I32 = gl::raw::INT,
        U32 = gl::raw::UNSIGNED_INT,
        DOUBLE = gl::raw::DOUBLE
    };

    template<typename T>
    constexpr Type gl_type() = delete;

    template<> constexpr Type gl_type<Float>() { return Type::FLOAT; }
    template<> constexpr Type gl_type<U8>() { return Type::U8; }
    template<> constexpr Type gl_type<I8>() { return Type::I8; }
    template<> constexpr Type gl_type<U16>() { return Type::U16; }
    template<> constexpr Type gl_type<I16>() { return Type::I16; }
    template<> constexpr Type gl_type<U32>() { return Type::U32; }
    template<> constexpr Type gl_type<I32>() { return Type::I32; }
    template<> constexpr Type gl_type<Double>() { return Type::DOUBLE; }

    namespace priv {
        template<Type T>
        struct from_gl_type;

        template<> struct from_gl_type<Type::FLOAT> { using type = Float; };
        template<> struct from_gl_type<Type::U8> { using type = U8; };
        template<> struct from_gl_type<Type::I8> { using type = I8; };
        template<> struct from_gl_type<Type::U16> { using type = U16; };
        template<> struct from_gl_type<Type::I16> { using type = I16; };
        template<> struct from_gl_type<Type::U32> { using type = U32; };
        template<> struct from_gl_type<Type::I32> { using type = I32; };
        template<> struct from_gl_type<Type::DOUBLE> { using type = Double; };
    }

    template<Type T>
    using from_gl_type = typename priv::from_gl_type<T>::type;
};
