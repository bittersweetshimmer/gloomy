#pragma once
#include <gloomy/Utilities/Tuple.hpp>

namespace gloomy {
	template<typename... Ts>
	using Vertex = gloomy::util::Tuple<Ts...>;
}