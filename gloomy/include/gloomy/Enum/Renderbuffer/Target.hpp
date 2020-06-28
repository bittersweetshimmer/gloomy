#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class RenderbufferTarget : gloomy::Enum {
        RENDERBUFFER = gl::raw::RENDERBUFFER
    };
}
