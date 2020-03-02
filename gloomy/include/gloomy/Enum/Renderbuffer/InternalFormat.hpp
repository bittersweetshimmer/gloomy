#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class RenderbufferInternalFormat : gloomy::Enum {
		DEPTH24_STENCIL8 = gl::raw::DEPTH24_STENCIL8
	};
}