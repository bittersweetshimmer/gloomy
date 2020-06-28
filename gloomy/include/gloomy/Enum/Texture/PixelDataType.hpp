#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Enum/Type.hpp>

namespace gloomy {
    enum class PixelDataType : gloomy::Enum {
         U8 = gl::raw::UNSIGNED_BYTE,
         I8 = gl::raw::BYTE,
         U16 = gl::raw::UNSIGNED_SHORT,
         I16 = gl::raw::SHORT,
         U32 = gl::raw::UNSIGNED_INT,
         I32 = gl::raw::INT,
         HALF_FLOAT = gl::raw::HALF_FLOAT,
         FLOAT = gl::raw::FLOAT,
         U8_3_3_2 = gl::raw::UNSIGNED_BYTE_3_3_2,
         U8_2_3_3_REV = gl::raw::UNSIGNED_BYTE_2_3_3_REV,
         U16_5_6_5 = gl::raw::UNSIGNED_SHORT_5_6_5,
         U16_5_6_5_REV = gl::raw::UNSIGNED_SHORT_5_6_5_REV,
         U16_4_4_4_4 = gl::raw::UNSIGNED_SHORT_4_4_4_4,
         U16_4_4_4_4_REV = gl::raw::UNSIGNED_SHORT_4_4_4_4_REV,
         U16_5_5_5_1 = gl::raw::UNSIGNED_SHORT_5_5_5_1,
         U16_1_5_5_5_REV = gl::raw::UNSIGNED_SHORT_1_5_5_5_REV,
         U32_8_8_8_8 = gl::raw::UNSIGNED_INT_8_8_8_8,
         U32_8_8_8_8_REV = gl::raw::UNSIGNED_INT_8_8_8_8_REV,
         U32_10_10_10_2 = gl::raw::UNSIGNED_INT_10_10_10_2,
         U32_2_10_10_10_REV = gl::raw::UNSIGNED_INT_2_10_10_10_REV
	};

    template<typename T>
    constexpr PixelDataType pixel_data_type() { return gloomy::to_enum<PixelDataType>(gloomy::from_enum(gloomy::gl_type<T>())); }

    template<PixelDataType T>
    using from_pixel_data_type = gloomy::from_gl_type<gloomy::to_enum<Type>(gloomy::from_enum(T))>;
}
