#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class ShaderKind : Enum {
        VERTEX = gl::VERTEX_SHADER,
        FRAGMENT = gl::FRAGMENT_SHADER,
        GEOMETRY = gl::GEOMETRY_SHADER,
        COMPUTE = gl::COMPUTE_SHADER,
        TESSALATION_CONTROL = gl::TESS_CONTROL_SHADER,
        TESSALATION_EVALUATION = gl::TESS_EVALUATION_SHADER
    };
}