#pragma once

#include <gloomy/API.hpp>

namespace gloomy {
	struct Primitive {
		PrimitiveKind kind = PrimitiveKind::TRIANGLES;
		IndexType index_type = IndexType::U32;
		gloomy::Size size = 0;

		Primitive(PrimitiveKind kind, IndexType index_type, gloomy::Size size) :
			kind(kind),
			index_type(index_type),
			size(size) {}

		template<typename T = gloomy::U32, PrimitiveKind kind = PrimitiveKind::TRIANGLES>
		constexpr static Primitive from(gloomy::Size size) { return Primitive(kind, gloomy::index_type<T>(), size); }

		inline void draw() const;
	};

	inline void Primitive::draw() const {
		gloomy::gl::draw_elements(this->kind, this->size, this->index_type);
	};
}