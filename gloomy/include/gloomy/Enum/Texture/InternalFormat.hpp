#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class TextureInternalFormat : gloomy::Enum {
        DEPTH = gl::raw::DEPTH_COMPONENT,
        DEPTH_STENCIL = gl::raw::DEPTH_STENCIL,
        RED = gl::raw::RED,
        RED_GREEN = gl::raw::RG,
        RGB = gl::raw::RGB,
        RGBA = gl::raw::RGBA,
        R8 = gl::raw::R8,
        R8_SNORM = gl::raw::R8_SNORM,
        R16 = gl::raw::R16,
        R16_SNORM = gl::raw::R16_SNORM,
        RG8 = gl::raw::RG8,
        RG8_SNORM = gl::raw::RG8_SNORM,
        RG16 = gl::raw::RG16,
        RG16_SNORM = gl::raw::RG16_SNORM,
        R3_G3_B2 = gl::raw::R3_G3_B2,
        RGB4 = gl::raw::RGB4,
        RGB5 = gl::raw::RGB5,
        RGB8 = gl::raw::RGB8,
        RGB8_SNORM = gl::raw::RGB8_SNORM,
        RGB10 = gl::raw::RGB10,
        RGB12 = gl::raw::RGB12,
        RGB16_SNORM = gl::raw::RGB16_SNORM,
        RGBA2 = gl::raw::RGBA2,
        RGBA4 = gl::raw::RGBA4,
        RGB5_A1 = gl::raw::RGB5_A1,
        RGBA8 = gl::raw::RGBA8,
        RGBA8_SNORM = gl::raw::RGBA8_SNORM,
        RGB10_A2 = gl::raw::RGB10_A2,
        RGB10_A2UI = gl::raw::RGB10_A2UI,
        RGBA12 = gl::raw::RGBA12,
        RGBA16 = gl::raw::RGBA16,
        SRGB8 = gl::raw::SRGB8,
        SRGB8_ALPHA8 = gl::raw::SRGB8_ALPHA8,
        R16F = gl::raw::R16F,
        RG16F = gl::raw::RG16F,
        RGB16F = gl::raw::RGB16F,
        RGBA16F = gl::raw::RGBA16F,
        R32F = gl::raw::R32F,
        RG32F = gl::raw::RG32F,
        RGB32F = gl::raw::RGB32F,
        RGBA32F = gl::raw::RGBA32F,
        R11F_G11F_B10F = gl::raw::R11F_G11F_B10F,
        RGB9_E5 = gl::raw::RGB9_E5,
        R8I = gl::raw::R8I,
        R8UI = gl::raw::R8UI,
        R16I = gl::raw::R16I,
        R16UI = gl::raw::R16UI,
        R32I = gl::raw::R32I,
        R32UI = gl::raw::R32UI,
        RG8I = gl::raw::RG8I,
        RG8UI = gl::raw::RG8UI,
        RG16I = gl::raw::RG16I,
        RG16UI = gl::raw::RG16UI,
        RG32I = gl::raw::RG32I,
        RG32UI = gl::raw::RG32UI,
        RGB8I = gl::raw::RGB8I,
        RGB8UI = gl::raw::RGB8UI,
        RGB16I = gl::raw::RGB16I,
        RGB16UI = gl::raw::RGB16UI,
        RGB32I = gl::raw::RGB32I,
        RGB32UI = gl::raw::RGB32UI,
        RGBA8I = gl::raw::RGBA8I,
        RGBA8UI = gl::raw::RGBA8UI,
        RGBA16I = gl::raw::RGBA16I,
        RGBA16UI = gl::raw::RGBA16UI,
        RGBA32I = gl::raw::RGBA32I,
        RGBA32UI = gl::raw::RGBA32UI,
        COMPRESSED_RED = gl::raw::COMPRESSED_RED,
        COMPRESSED_RG = gl::raw::COMPRESSED_RG,
        COMPRESSED_RGB = gl::raw::COMPRESSED_RGB,
        COMPRESSED_RGBA = gl::raw::COMPRESSED_RGBA,
        COMPRESSED_SRGB = gl::raw::COMPRESSED_SRGB,
        COMPRESSED_SRGB_ALPHA = gl::raw::COMPRESSED_SRGB_ALPHA,
        COMPRESSED_RED_RGTC1 = gl::raw::COMPRESSED_RED_RGTC1,
        COMPRESSED_SIGNED_RED_RGTC1 = gl::raw::COMPRESSED_SIGNED_RED_RGTC1,
        COMPRESSED_RG_RGTC2 = gl::raw::COMPRESSED_RG_RGTC2,
        COMPRESSED_SIGNED_RG_RGTC2 = gl::raw::COMPRESSED_SIGNED_RG_RGTC2,
        COMPRESSED_RGBA_BPTC_UNORM = gl::raw::COMPRESSED_RGBA_BPTC_UNORM,
        COMPRESSED_SRGB_ALPHA_BPTC_UNORM = gl::raw::COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
        COMPRESSED_RGB_BPTC_SIGNED_FLOAT = gl::raw::COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
        COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = gl::raw::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
    };
}
