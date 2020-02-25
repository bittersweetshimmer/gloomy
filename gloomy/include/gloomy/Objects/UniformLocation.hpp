#pragma once
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Utilities/Distinct.hpp>

namespace gloomy {
    using UniformLocation = gloomy::util::Distinct<gloomy::I32, struct UniformLocationTag>;
}