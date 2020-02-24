#pragma once
#include <gloomy/gl.hpp>
#include <gloomy/Conversion/Enum.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/GL/Raw/Enum.hpp>

namespace gloomy {
    enum class ShaderKind : Enum {
        VERTEX = gl::raw::VERTEX_SHADER,
        FRAGMENT = gl::raw::FRAGMENT_SHADER,
        GEOMETRY = gl::raw::GEOMETRY_SHADER,
        COMPUTE = gl::raw::COMPUTE_SHADER,
        TESSALATION_CONTROL = gl::raw::TESS_CONTROL_SHADER,
        TESSALATION_EVALUATION = gl::raw::TESS_EVALUATION_SHADER
    };
}