#pragma once

#include <gloomy/Enum/PrimitiveKind.hpp>
#include <gloomy/Enum/Type.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Enum/Buffer/IndexType.hpp>

namespace gloomy {
	template<typename T>
	inline void draw_indexed(PrimitiveKind kind, gloomy::Size size) {
		gloomy::gl::draw_elements(kind, size, gloomy::index_type<T>());
	};

	template<typename T>
	inline void fill(T& color) {
		GLOOMY_CHECK(gloomy::gl::raw::clear_color(color[0], color[1], color[2], color[3]));
		GLOOMY_CHECK(gloomy::gl::raw::clear(gloomy::gl::raw::COLOR_BUFFER_BIT));
	}

	inline void fill(gloomy::Float red = 0.0f, gloomy::Float green = 0.0f, gloomy::Float blue = 0.0f, gloomy::Float alpha = 0.0f) {
		GLOOMY_CHECK(gloomy::gl::raw::clear_color(red, green, blue, alpha));
		GLOOMY_CHECK(gloomy::gl::raw::clear(gloomy::gl::raw::COLOR_BUFFER_BIT));
	}
}