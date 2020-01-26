#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class TextureTarget : gl::Enum {
		TEXTURE_1D = gl::TEXTURE_1D,
		TEXTURE_1D_ARRAY = gl::TEXTURE_1D_ARRAY,
		TEXTURE_2D = gl::TEXTURE_2D,
		TEXTURE_2D_ARRAY = gl::TEXTURE_2D_ARRAY,
		TEXTURE_2D_MULTISAMPLE = gl::TEXTURE_2D_MULTISAMPLE,
		TEXTURE_2D_MULTISAMPLE_ARRAY = gl::TEXTURE_2D_MULTISAMPLE_ARRAY,
		TEXTURE_3D = gl::TEXTURE_3D,
		TEXTURE_CUBE_MAP = gl::TEXTURE_CUBE_MAP,
		TEXTURE_CUBE_MAP_ARRAY = gl::TEXTURE_CUBE_MAP_ARRAY,
		TEXTURE_RECTANGLE = gl::TEXTURE_RECTANGLE
	};
}