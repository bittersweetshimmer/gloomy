#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class FramebufferAttachment : gloomy::Enum {
		COLOR_ATTACHMENT0 = gl::raw::COLOR_ATTACHMENT0,
		DEPTH_ATTACHMENT = gl::raw::DEPTH_ATTACHMENT,
		STENCIL_ATTACHMENT = gl::raw::STENCIL_ATTACHMENT,
        DEPTH_STENCIL_ATTACHMENT = gl::raw::DEPTH_STENCIL_ATTACHMENT
	};
}