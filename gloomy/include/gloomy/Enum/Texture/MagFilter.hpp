#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class TextureMagFilter : gloomy::Enum {
        NEAREST = gl::raw::NEAREST,
        LINEAR = gl::raw::LINEAR
    };
}
