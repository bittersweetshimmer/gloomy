#pragma once

#include <gloomy/Enum/PrimitiveKind.hpp>
#include <gloomy/Enum/Type.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Enum/Buffer/IndexType.hpp>

namespace gloomy {
	template<PrimitiveKind kind, typename T> 
	void draw_primitives(gloomy::Size size) {
		gl::draw_elements(gloomy::from_enum(kind), size, gloomy::from_enum(gloomy::gl_type<T>()), 0);
	};

	template<typename T>
	void draw_triangles(gloomy::Size size) {
		gloomy::draw_primitives<PrimitiveKind::TRIANGLES, T>(size);
	};

	template<typename T>
	void draw_lines(gloomy::Size size) {
		gloomy::draw_primitives<PrimitiveKind::LINES, T>(size);
	};

	struct Primitive {
		PrimitiveKind kind = PrimitiveKind::TRIANGLES;
		IndexType index_type = IndexType::U32;
		gloomy::Size size = 0;

		Primitive(PrimitiveKind kind, IndexType index_type, gloomy::Size size) :
			kind(kind),
			index_type(index_type),
			size(size) {}

		template<typename T = gloomy::U32, PrimitiveKind kind = PrimitiveKind::TRIANGLES>
		inline static Primitive from(gloomy::Size size) { return Primitive(kind, gloomy::index_type<T>(), size); }

		inline void draw() const;
	};

	inline void Primitive::draw() const {
		gl::draw_elements(gloomy::from_enum(this->kind), this->size, gloomy::from_enum(this->index_type), 0);
	};
}