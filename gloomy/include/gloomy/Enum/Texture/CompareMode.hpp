#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class TextureCompareMode : gloomy::Enum {
        REF_TO_TEXTURE = gl::raw::COMPARE_REF_TO_TEXTURE,
        NONE = gl::raw::NONE
    };
}
