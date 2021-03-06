#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class BufferKind : gloomy::Enum {
        ARRAY_BUFFER = gl::raw::ARRAY_BUFFER,
        ATOMIC_COUNTER_BUFFER = gl::raw::ATOMIC_COUNTER_BUFFER,
        COPY_READ_BUFFER = gl::raw::COPY_READ_BUFFER,
        COPY_WRITE_BUFFER = gl::raw::COPY_WRITE_BUFFER,
        DISPATCH_INDIRECT_BUFFER = gl::raw::DISPATCH_INDIRECT_BUFFER,
        DRAW_INDIRECT_BUFFER = gl::raw::DRAW_INDIRECT_BUFFER,
        ELEMENT_ARRAY_BUFFER = gl::raw::ELEMENT_ARRAY_BUFFER,
        PIXEL_PACK_BUFFER = gl::raw::PIXEL_PACK_BUFFER,
        PIXEL_UNPACK_BUFFER = gl::raw::PIXEL_UNPACK_BUFFER,
        QUERY_BUFFER = gl::raw::QUERY_BUFFER,
        SHADER_STORAGE_BUFFER = gl::raw::SHADER_STORAGE_BUFFER,
        TEXTURE_BUFFER = gl::raw::TEXTURE_BUFFER,
        TRANSFORM_FEEDBACK_BUFFER = gl::raw::TRANSFORM_FEEDBACK_BUFFER,
        UNIFORM_BUFFER = gl::raw::UNIFORM_BUFFER
    };
}
