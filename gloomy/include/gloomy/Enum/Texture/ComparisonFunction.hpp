#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class TextureComparisonFunction : gloomy::Enum {
        LEQUAL = gl::raw::LEQUAL,
        GEQUAL = gl::raw::GEQUAL,
        LESS = gl::raw::LESS,
        GREATER = gl::raw::GREATER,
        EQUAL = gl::raw::EQUAL,
        NOTEQUAL = gl::raw::NOTEQUAL,
        ALWAYS = gl::raw::ALWAYS,
        NEVER = gl::raw::NEVER
    };
}
