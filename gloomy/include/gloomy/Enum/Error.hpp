#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class Error {
        NONE = gl::NO_ERROR_GL,
        INVALID_ENUM = gl::INVALID_ENUM,
        INVALID_VALUE = gl::INVALID_VALUE,
        INVALID_OPERATION = gl::INVALID_OPERATION,
        INVALID_FRAMEBUFFER_OPERATION = gl::INVALID_FRAMEBUFFER_OPERATION,
        OUT_OF_MEMORY = gl::OUT_OF_MEMORY,
        STACK_UNDERFLOW = gl::STACK_UNDERFLOW,
        STACK_OVERFLOW = gl::STACK_OVERFLOW
	};
}