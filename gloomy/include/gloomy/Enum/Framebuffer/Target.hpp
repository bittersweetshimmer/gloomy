#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class FramebufferTarget : gloomy::Enum {
		DRAW_FRAMEBUFFER = gl::raw::DRAW_FRAMEBUFFER,
		READ_FRAMEBUFFER = gl::raw::READ_FRAMEBUFFER,
		FRAMEBUFFER = gl::raw::FRAMEBUFFER
	};
}