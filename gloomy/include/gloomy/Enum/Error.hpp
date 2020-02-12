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

        constexpr const char* error_message(Error error) {
                if (error == Error::NONE) return "no error";
                else if (error == Error::INVALID_ENUM) return "invalid enum";
                else if (error == Error::INVALID_VALUE) return "invalid value";
                else if (error == Error::INVALID_OPERATION) return "invalid operation";
                else if (error == Error::INVALID_FRAMEBUFFER_OPERATION) return "invalid framebuffer operation";
                else if (error == Error::OUT_OF_MEMORY) return "out of memory";
                else if (error == Error::STACK_UNDERFLOW) return "stack underflow";
                else if (error == Error::STACK_OVERFLOW) return "stack overflow";
        };
}