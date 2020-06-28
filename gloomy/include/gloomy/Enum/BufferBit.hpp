#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Utilities/BitMask.hpp>

namespace gloomy {
    enum class BufferBit : gloomy::Bitfield {
        COLOR = gl::raw::COLOR_BUFFER_BIT,
        DEPTH = gl::raw::DEPTH_BUFFER_BIT,
        STENCIL = gl::raw::STENCIL_BUFFER_BIT,
    };

    BITMASK_DEFINE_MAX_ELEMENT(gloomy::BufferBit, COLOR)
}
