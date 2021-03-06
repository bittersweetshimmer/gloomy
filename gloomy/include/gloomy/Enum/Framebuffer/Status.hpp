#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class FramebufferStatus : gloomy::Enum {
        FRAMEBUFFER_COMPLETE = gl::raw::FRAMEBUFFER_COMPLETE,
        FRAMEBUFFER_UNDEFINED = gl::raw:: FRAMEBUFFER_UNDEFINED,
        FRAMEBUFFER_INCOMPLETE_ATTACHMENT = gl::raw::FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
        FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = gl::raw::FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
        FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = gl::raw::FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
        FRAMEBUFFER_INCOMPLETE_READ_BUFFER = gl::raw::FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
        FRAMEBUFFER_UNSUPPORTED = gl::raw::FRAMEBUFFER_UNSUPPORTED,
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = gl::raw::FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
        FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = gl::raw::FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
    };
}
