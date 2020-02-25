#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class PrimitiveKind : Enum {
	    POINTS = gl::raw::POINTS,
        LINE_STRIP = gl::raw::LINE_STRIP,
        LINE_LOOP = gl::raw::LINE_LOOP,
        LINES = gl::raw::LINES,
        LINE_STRIP_ADJACENCY = gl::raw::LINE_STRIP_ADJACENCY,
        LINES_ADJACENCY = gl::raw::LINES_ADJACENCY,
        TRIANGLE_STRIP = gl::raw::TRIANGLE_STRIP,
        TRIANGLE_FAN = gl::raw::TRIANGLE_FAN,
        TRIANGLES = gl::raw::TRIANGLES,
        TRIANGLE_STRIP_ADJACENCY = gl::raw::TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY = gl::raw::TRIANGLES_ADJACENCY,
        PATCHES = gl::raw::PATCHES
	};
}