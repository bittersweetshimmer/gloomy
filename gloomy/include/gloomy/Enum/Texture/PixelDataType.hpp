#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Enum/Type.hpp>

namespace gloomy {
    enum class PixelDataType : Enum {
         U8 = gl::UNSIGNED_BYTE,
         I8 = gl::BYTE,
         U16 = gl::UNSIGNED_SHORT,
         I16 = gl::SHORT,
         U32 = gl::UNSIGNED_INT,
         I32 = gl::INT,
         HALF_FLOAT = gl::HALF_FLOAT,
         FLOAT = gl::FLOAT,
         U8_3_3_2 = gl::UNSIGNED_BYTE_3_3_2,
         U8_2_3_3_REV = gl::UNSIGNED_BYTE_2_3_3_REV,
         U16_5_6_5 = gl::UNSIGNED_SHORT_5_6_5,
         U16_5_6_5_REV = gl::UNSIGNED_SHORT_5_6_5_REV,
         U16_4_4_4_4 = gl::UNSIGNED_SHORT_4_4_4_4,
         U16_4_4_4_4_REV = gl::UNSIGNED_SHORT_4_4_4_4_REV,
         U16_5_5_5_1 = gl::UNSIGNED_SHORT_5_5_5_1,
         U16_1_5_5_5_REV = gl::UNSIGNED_SHORT_1_5_5_5_REV,
         U32_8_8_8_8 = gl::UNSIGNED_INT_8_8_8_8,
         U32_8_8_8_8_REV = gl::UNSIGNED_INT_8_8_8_8_REV,
         U32_10_10_10_2 = gl::UNSIGNED_INT_10_10_10_2,
         U32_2_10_10_10_REV = gl::UNSIGNED_INT_2_10_10_10_REV
	};

    template<typename T>
    constexpr PixelDataType to_pixel_data_type() { return gloomy::to_enum<PixelDataType>(gloomy::from_enum(gloomy::gl_type<T>())); }

    template<PixelDataType T>
    using from_pixel_data_type = gloomy::from_gl_type<gloomy::to_enum<Type>(gloomy::from_enum(T))>;
};