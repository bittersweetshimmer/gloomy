#pragma once

#include <cassert>
#include <memory>

#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Objects/ID.hpp>

#include <gloomy/Sources/BufferView.hpp>

#include <gloomy/Enum/Shader/Kind.hpp>
#include <gloomy/Enum/Buffer/Kind.hpp>
#include <gloomy/Enum/Buffer/Usage.hpp>

#include <gloomy/Enum/Texture/Kind.hpp>
#include <gloomy/Enum/Texture/Target.hpp>

#include <gloomy/Enum/PrimitiveKind.hpp>
#include <gloomy/Enum/Buffer/IndexType.hpp>

namespace gloomy::gl {
    template<typename T>
    inline void draw_elements(gloomy::PrimitiveKind kind, gloomy::Size size, gloomy::IndexType type, const T& container) {
        GLOOMY_CHECK(gl::raw::draw_elements(gloomy::from_enum(kind), size, gloomy::from_enum(type), container.data()));
    };

    inline void draw_elements(gloomy::PrimitiveKind kind, gloomy::Size size, gloomy::IndexType type) {
        GLOOMY_CHECK(gl::raw::draw_elements(gloomy::from_enum(kind), size, gloomy::from_enum(type), nullptr));
    };

    inline void draw_arrays(gloomy::PrimitiveKind kind, gloomy::Size count) {
        GLOOMY_CHECK(gl::raw::draw_arrays(gloomy::from_enum(kind), 0, count));
    };

    inline void draw_arrays(gloomy::PrimitiveKind kind, gloomy::U32 first, gloomy::Size count) {
        GLOOMY_CHECK(gl::raw::draw_arrays(gloomy::from_enum(kind), static_cast<gloomy::I32>(first), count));
    };

    inline void use_program(gloomy::RawID id) {
        assert(id != 0 && "Binding not generated Program.");
        GLOOMY_CHECK(gl::raw::use_program(id));
    };

    inline void unbind_program() {
        GLOOMY_CHECK(gl::raw::use_program(gloomy::null_raw_id));
    };

	inline gloomy::RawID create_program() {
        gloomy::RawID id;
        GLOOMY_CHECK(id = gl::raw::create_program());
        return id;
    };

    inline void delete_program(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Program.");
        GLOOMY_CHECK(gl::raw::delete_program(id));
    };

	inline gloomy::RawID create_shader(ShaderKind kind) {
        gloomy::RawID id;
        GLOOMY_CHECK(id = gl::raw::create_shader(gloomy::from_enum(kind)));
        return id;
    };

    inline void delete_shader(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Shader.");
        GLOOMY_CHECK(gl::raw::delete_shader(id));
    };

    inline gloomy::RawID gen_buffer() { 
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_buffers(1, &raw_id));
        return raw_id;
    };

    inline void delete_buffer(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Buffer.");
        GLOOMY_CHECK(gl::raw::delete_buffers(1, &id));
    };

    inline void bind_buffer(gloomy::BufferKind target, gloomy::RawID id) {
        assert(id != 0 && "Binding non-generated Buffer.");
        GLOOMY_CHECK(gl::raw::bind_buffer(gloomy::from_enum(target), id)); 
    };

    inline void unbind_buffer(gloomy::BufferKind target) {
        GLOOMY_CHECK(gl::raw::bind_buffer(gloomy::from_enum(target), gloomy::null_raw_id)); 
    };

    inline void buffer_data(gloomy::BufferKind target, const gloomy::src::BufferView& view, gloomy::BufferUsage usage) {
        GLOOMY_CHECK(gl::raw::buffer_data(gloomy::from_enum(target), view.size, view.data, gloomy::from_enum(usage.combined())));
    };

	inline gloomy::RawID gen_texture() { 
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_textures(1, &raw_id));
        return raw_id;
    };

    inline void delete_texture(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Texture.");
        GLOOMY_CHECK(gl::raw::delete_textures(1, &id));
    };

    inline void bind_texture(gloomy::TextureTarget target, gloomy::RawID id) {
        assert(id != 0 && "Binding non-generated Texture.");
        GLOOMY_CHECK(gl::raw::bind_texture(gloomy::from_enum(target), id)); 
    };

    inline void unbind_texture(gloomy::TextureTarget target) {
        GLOOMY_CHECK(gl::raw::bind_texture(gloomy::from_enum(target), gloomy::null_raw_id)); 
    };

    inline void active_texture(size_t index) { (gl::raw::active_texture(gl::raw::TEXTURE0 + index)); }
}