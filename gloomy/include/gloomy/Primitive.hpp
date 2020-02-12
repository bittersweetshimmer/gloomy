#pragma once

#include <gloomy/Enum/PrimitiveKind.hpp>
#include <gloomy/Enum/Type.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Enum/Buffer/IndexType.hpp>

namespace gloomy {
	void draw_primitives(PrimitiveKind kind, gloomy::Size size, gloomy::IndexType type) {
		GLOOMY_CHECK(gl::draw_elements(gloomy::from_enum(kind), size, gloomy::from_enum(type), 0));
	};

	void draw_triangles(gloomy::Size size, gloomy::IndexType type) {
		gloomy::draw_primitives(PrimitiveKind::TRIANGLES, size, type);
	};

	void draw_lines(gloomy::Size size, gloomy::IndexType type) {
		gloomy::draw_primitives(PrimitiveKind::LINES, size, type);
	};

	template<typename T>
	void draw_triangles(gloomy::Size size) {
		gloomy::draw_primitives(PrimitiveKind::TRIANGLES, size, gloomy::index_type<T>());
	};

	template<typename T>
	void draw_lines(gloomy::Size size) {
		gloomy::draw_primitives(PrimitiveKind::LINES, size, gloomy::index_type<T>());
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
		gloomy::draw_primitives(this->kind, this->size, this->index_type);
	};
}