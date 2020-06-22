#pragma once

#include <cassert>
#include <memory>
#include <bitset>

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

#include <gloomy/Objects/UniformLocation.hpp>
#include <gloomy/Enum/BufferBit.hpp>
#include <gloomy/Enum/Capability.hpp>

#include <gloomy/Enum/Framebuffer/Target.hpp>
#include <gloomy/Enum/Framebuffer/Status.hpp>

#include <gloomy/Enum/Renderbuffer/Target.hpp>
#include <gloomy/Enum/Renderbuffer/InternalFormat.hpp>

#include <gloomy/Enum/Framebuffer/Attachment.hpp>
#include <gloomy/Enum/Framebuffer/TextureTarget.hpp>

namespace gloomy::gl {
    inline void disable(gloomy::Capability cap) {
        GLOOMY_CHECK(gl::raw::disable(gloomy::from_enum(cap)));
    }

    inline void enable(gloomy::Capability cap) {
        GLOOMY_CHECK(gl::raw::enable(gloomy::from_enum(cap)));
    }

    inline void clear(util::Bitmask<gloomy::BufferBit> mask) {
        GLOOMY_CHECK(gl::raw::clear(mask.bits()));
    }

    inline void clear_color(gloomy::Float red, gloomy::Float green, gloomy::Float blue, gloomy::Float alpha) { GLOOMY_CHECK(gl::raw::clear_color(red, green, blue, alpha)); }

    inline void draw_elements_instanced(gloomy::PrimitiveKind kind, gloomy::Size size, gloomy::IndexType type, gloomy::Size instance_count, const void* indices = nullptr) {
        GLOOMY_CHECK(gl::raw::draw_elements_instanced(gloomy::from_enum(kind), size, gloomy::from_enum(type), indices, instance_count));
    }

    inline void draw_elements(gloomy::PrimitiveKind kind, gloomy::Size size, gloomy::IndexType type, gloomy::SizeIPointer offset = 0u) {
        GLOOMY_CHECK(gl::raw::draw_elements(gloomy::from_enum(kind), size, gloomy::from_enum(type), reinterpret_cast<const void*>(offset)));
    }

    inline void draw_arrays_instanced(gloomy::PrimitiveKind kind, gloomy::I32 first, gloomy::Size count, gloomy::Size instance_count) {
        GLOOMY_CHECK(gl::raw::draw_arrays_instanced(gloomy::from_enum(kind), first, count, instance_count));
    }

    inline void draw_arrays_instanced(gloomy::PrimitiveKind kind, gloomy::Size count, gloomy::Size instance_count) {
        GLOOMY_CHECK(gl::raw::draw_arrays_instanced(gloomy::from_enum(kind), 0, count, instance_count));
    }

    inline void draw_arrays(gloomy::PrimitiveKind kind, gloomy::Size count) {
        GLOOMY_CHECK(gl::raw::draw_arrays(gloomy::from_enum(kind), 0, count));
    }

    inline void draw_arrays(gloomy::PrimitiveKind kind, gloomy::I32 first, gloomy::Size count) {
        GLOOMY_CHECK(gl::raw::draw_arrays(gloomy::from_enum(kind), first, count));
    }

    inline void use_program(gloomy::RawID id) {
        assert(id != 0 && "Binding not generated Program.");
        GLOOMY_CHECK(gl::raw::use_program(id));
    }

    inline void unbind_program() {
        GLOOMY_CHECK(gl::raw::use_program(gloomy::null_raw_id));
    }

	inline gloomy::RawID create_program() {
        gloomy::RawID id;
        GLOOMY_CHECK(id = gl::raw::create_program());
        return id;
    }

    inline void bind_renderbuffer(gloomy::RenderbufferTarget target, gloomy::RawID id) {
        assert(id != 0 && "Binding not generated Renderbuffer.");
        GLOOMY_CHECK(gl::raw::bind_renderbuffer(gloomy::from_enum(target), id));
    }

    inline void unbind_renderbuffer(gloomy::RenderbufferTarget target) {
        GLOOMY_CHECK(gl::raw::bind_renderbuffer(gloomy::from_enum(target), gloomy::null_raw_id));
    }

    inline void delete_renderbuffer(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Renderbuffer.");
        GLOOMY_CHECK(gl::raw::delete_renderbuffers(1, &id));
    }

	inline gloomy::RawID gen_renderbuffer() {
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_renderbuffers(1, &raw_id));
        return raw_id;
    }

    inline void renderbuffer_storage(gloomy::RenderbufferTarget target, gloomy::RenderbufferInternalFormat format, gloomy::U32 width, gloomy::U32 height) {
        GLOOMY_CHECK(gloomy::gl::raw::renderbuffer_storage(gloomy::from_enum(target), gloomy::from_enum(format), static_cast<gloomy::Size>(width), static_cast<gloomy::Size>(height)));
    }

    inline void framebuffer_texture2d(gloomy::FramebufferTarget target, gloomy::FramebufferAttachment attachment, gloomy::FramebufferTextureTarget tex_target, gloomy::RawID texture, gloomy::I32 level = 0) {
        GLOOMY_CHECK(gloomy::gl::raw::framebuffer_texture2d(gloomy::from_enum(target), gloomy::from_enum(attachment), gloomy::from_enum(tex_target), texture, level));
    }

    inline void framebuffer_renderbuffer(gloomy::FramebufferTarget target, gloomy::FramebufferAttachment attachment, gloomy::RenderbufferTarget renderbuffer_target, gloomy::RawID renderbuffer) {
        GLOOMY_CHECK(gloomy::gl::raw::framebuffer_renderbuffer(gloomy::from_enum(target), gloomy::from_enum(attachment), gloomy::from_enum(renderbuffer_target), renderbuffer));
    } 

    inline void bind_framebuffer(gloomy::FramebufferTarget target, gloomy::RawID id) {
        assert(id != 0 && "Binding not generated Framebuffer.");
        GLOOMY_CHECK(gl::raw::bind_framebuffer(gloomy::from_enum(target), id));
    }

    inline void unbind_framebuffer(gloomy::FramebufferTarget target) {
        GLOOMY_CHECK(gl::raw::bind_framebuffer(gloomy::from_enum(target), gloomy::null_raw_id));
    }

    inline void delete_framebuffer(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Framebuffer.");
        GLOOMY_CHECK(gl::raw::delete_framebuffers(1, &id));
    }

	inline gloomy::RawID gen_framebuffer() {
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_framebuffers(1, &raw_id));
        return raw_id;
    }

    inline gloomy::FramebufferStatus check_framebuffer_status(gloomy::FramebufferTarget target) {
        gloomy::Enum status;
        GLOOMY_CHECK(status = gloomy::gl::raw::check_framebuffer_status(gloomy::from_enum(target)));
        return gloomy::to_enum<gloomy::FramebufferStatus>(status);
    }

    inline void delete_program(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Program.");
        GLOOMY_CHECK(gl::raw::delete_program(id));
    }

	inline gloomy::RawID create_shader(ShaderKind kind) {
        gloomy::RawID id;
        GLOOMY_CHECK(id = gl::raw::create_shader(gloomy::from_enum(kind)));
        return id;
    }

    inline void delete_shader(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Shader.");
        GLOOMY_CHECK(gl::raw::delete_shader(id));
    }

    inline gloomy::RawID gen_buffer() { 
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_buffers(1, &raw_id));
        return raw_id;
    }

    inline void delete_buffer(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Buffer.");
        GLOOMY_CHECK(gl::raw::delete_buffers(1, &id));
    }

    inline void bind_buffer(gloomy::BufferKind target, gloomy::RawID id) {
        assert(id != 0 && "Binding non-generated Buffer.");
        GLOOMY_CHECK(gl::raw::bind_buffer(gloomy::from_enum(target), id)); 
    }

    inline void unbind_buffer(gloomy::BufferKind target) {
        GLOOMY_CHECK(gl::raw::bind_buffer(gloomy::from_enum(target), gloomy::null_raw_id)); 
    }

    inline void buffer_data(gloomy::BufferKind target, const gloomy::src::BufferView& view, gloomy::BufferUsage usage) {
        GLOOMY_CHECK(gl::raw::buffer_data(gloomy::from_enum(target), view.size, view.data, gloomy::from_enum(usage.combined())));
    }

	inline gloomy::RawID gen_texture() { 
        auto raw_id = gloomy::null_raw_id;
        GLOOMY_CHECK(gloomy::gl::raw::gen_textures(1, &raw_id));
        return raw_id;
    }

    inline void delete_texture(gloomy::RawID id) {
        assert(id != 0 && "Releasing null Texture.");
        GLOOMY_CHECK(gl::raw::delete_textures(1, &id));
    }

    inline void bind_texture(gloomy::TextureTarget target, gloomy::RawID id) {
        assert(id != 0 && "Binding non-generated Texture.");
        GLOOMY_CHECK(gl::raw::bind_texture(gloomy::from_enum(target), id)); 
    }

    inline void unbind_texture(gloomy::TextureTarget target) {
        GLOOMY_CHECK(gl::raw::bind_texture(gloomy::from_enum(target), gloomy::null_raw_id)); 
    }

    inline void active_texture(size_t index) { GLOOMY_CHECK(gl::raw::active_texture(gl::raw::TEXTURE0 + static_cast<gloomy::Enum>(index))); }

    inline void bind_texture_at_slot(gloomy::TextureTarget target, gloomy::RawID id, size_t index) {
        gl::active_texture(index);
        gl::bind_texture(target, id);
    }

    inline UniformLocation get_uniform_location(gloomy::RawID program, const std::string& name) {
        gloomy::I32 location = 0;
        GLOOMY_CHECK(location = gl::raw::get_uniform_location(program, name.c_str()));

        return UniformLocation(location);
    }

    template<typename T, size_t M, size_t N>
    inline void set_uniform(const gloomy::UniformLocation& location, const T* value, gloomy::Size count = 1, gloomy::Bool transpose = false) {
        static_assert(M >= 1 && M <= 4);
        static_assert(N >= 1 && N <= 4);
        static_assert(std::is_same_v<T, gloomy::Float> || std::is_same_v<T, gloomy::I32> || std::is_same_v<T, gloomy::U32>);

        if constexpr (std::is_same_v<T, gloomy::Float>) {
            if constexpr (M == 1) {
                static_assert(N == 1);
                GLOOMY_CHECK(gl::raw::uniform_1fv(location.get(), count, value));
            }
            else if constexpr (M == 2) {
                if constexpr (N == 1) { GLOOMY_CHECK(gl::raw::uniform_2fv(location.get(), count, value)); }
                else if constexpr (N == 2) { GLOOMY_CHECK(gl::raw::uniform_mat2fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 3) { GLOOMY_CHECK(gl::raw::uniform_mat2x3fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 4) { GLOOMY_CHECK(gl::raw::uniform_mat2x4fv(location.get(), count, transpose, value)); }
                return;
            }
            else if constexpr (M == 3) {
                if constexpr (N == 1) { GLOOMY_CHECK(gl::raw::uniform_3fv(location.get(), count, value)); }
                else if constexpr (N == 2) { GLOOMY_CHECK(gl::raw::uniform_mat3x2fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 3) { GLOOMY_CHECK(gl::raw::uniform_mat3fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 4) { GLOOMY_CHECK(gl::raw::uniform_mat3x4fv(location.get(), count, transpose, value)); }
                return;
            }
            else if constexpr (M == 4) {
                if constexpr (N == 1) { GLOOMY_CHECK(gl::raw::uniform_4fv(location.get(), count, value)); }
                else if constexpr (N == 2) { GLOOMY_CHECK(gl::raw::uniform_mat4x2fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 3) { GLOOMY_CHECK(gl::raw::uniform_mat4x3fv(location.get(), count, transpose, value)); }
                else if constexpr (N == 4) { GLOOMY_CHECK(gl::raw::uniform_mat4fv(location.get(), count, transpose, value)); }
                return;
            }
        }
        else if constexpr (std::is_same_v<T, gloomy::I32>) {
            static_assert(N == 1);

            if constexpr (M == 1) { GLOOMY_CHECK(gl::raw::uniform_1iv(location.get(), count, value)); }
            else if constexpr (M == 2) { GLOOMY_CHECK(gl::raw::uniform_2iv(location.get(), count, value)); }
            else if constexpr (M == 3) { GLOOMY_CHECK(gl::raw::uniform_3iv(location.get(), count, value)); }
            else if constexpr (M == 4) { GLOOMY_CHECK(gl::raw::uniform_4iv(location.get(), count, value)); }
        }
        else if constexpr (std::is_same_v<T, gloomy::U32>) {
            static_assert(N == 1);

            if constexpr (M == 1) { GLOOMY_CHECK(gl::raw::uniform_1uiv(location.get(), count, value)); }
            else if constexpr (M == 2) { GLOOMY_CHECK(gl::raw::uniform_2uiv(location.get(), count, value)); }
            else if constexpr (M == 3) { GLOOMY_CHECK(gl::raw::uniform_3uiv(location.get(), count, value)); }
            else if constexpr (M == 4) { GLOOMY_CHECK(gl::raw::uniform_4uiv(location.get(), count, value)); }
        }
    }

    template<typename T, size_t M>
    inline void set_uniform_vec(const gloomy::UniformLocation& location, const T* value, gloomy::Size count = 1) {
        gl::set_uniform<T, M, 1>(location, value, count);
    }

    template<typename T, size_t M>
    inline void set_uniform_mat(const gloomy::UniformLocation& location, const T* value, gloomy::Size count = 1, gloomy::Bool transpose = false) {
        gl::set_uniform<T, M, M>(location, value, count, transpose);
    }

    template<typename T, typename... Ts>
    inline void set_uniform_by_values(const gloomy::UniformLocation& location, Ts&&... values) {
        constexpr static auto M = sizeof...(Ts);
        static_assert(M >= 1 && M <= 4);
        static_assert(std::is_same_v<T, gloomy::Float> || std::is_same_v<T, gloomy::I32> || std::is_same_v<T, gloomy::U32>);

        if constexpr (std::is_same_v<T, gloomy::Float>) {
            if constexpr (M == 1) { gl::raw::uniform_1f(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 2) { gl::raw::uniform_2f(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 3) { gl::raw::uniform_3f(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 4) { gl::raw::uniform_4f(location.get(), static_cast<T>(values)...); }
        }
        else if constexpr (std::is_same_v<T, gloomy::I32>) {
            if constexpr (M == 1) { gl::raw::uniform_1i(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 2) { gl::raw::uniform_2i(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 3) { gl::raw::uniform_3i(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 4) { gl::raw::uniform_4i(location.get(), static_cast<T>(values)...); }
        }
        else if constexpr (std::is_same_v<T, gloomy::U32>) {
            if constexpr (M == 1) { gl::raw::uniform_1ui(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 2) { gl::raw::uniform_2ui(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 3) { gl::raw::uniform_3ui(location.get(), static_cast<T>(values)...); }
            else if constexpr (M == 4) { gl::raw::uniform_4ui(location.get(), static_cast<T>(values)...); }
        }
    }
}
