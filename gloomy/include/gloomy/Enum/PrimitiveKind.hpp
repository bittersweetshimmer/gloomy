#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
	enum class PrimitiveKind : Enum {
	    POINTS = gl::POINTS,
        LINE_STRIP = gl::LINE_STRIP,
        LINE_LOOP = gl::LINE_LOOP,
        LINES = gl::LINES,
        LINE_STRIP_ADJACENCY = gl::LINE_STRIP_ADJACENCY,
        LINES_ADJACENCY = gl::LINES_ADJACENCY,
        TRIANGLE_STRIP = gl::TRIANGLE_STRIP,
        TRIANGLE_FAN = gl::TRIANGLE_FAN,
        TRIANGLES = gl::TRIANGLES,
        TRIANGLE_STRIP_ADJACENCY = gl::TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY = gl::TRIANGLES_ADJACENCY,
        PATCHES = gl::PATCHES
	};
}