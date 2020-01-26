#pragma once
#include <optional>
#include <functional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Sources/Shader.hpp>
#include <gloomy/Enum/Shader/Kind.hpp>
#include <gloomy/Utilities/CopyOnWrite.hpp>

namespace gloomy {
    template<ShaderKind kind>
    struct Shader : public Object<Shader<kind>>, public Committable<Shader<kind>> {
        using Object<Shader<kind>>::Object;

        Shader() : source(gloomy::src::Shader<kind>()) {}
        Shader(gloomy::src::Shader<kind>&& shader_source) : source(std::move(shader_source)) {};
        Shader(const gloomy::src::Shader<kind>& shader_source) : source(shader_source) {};
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        constexpr static ShaderKind kind = kind;

        util::Cow<gloomy::src::Shader<kind>> source;
    };

    template<ShaderKind kind> struct ObjectTrait<Shader<kind>> {
        static inline ID<Shader<kind>> generate() { ID<Shader<kind>> id; id.get() = gl::create_shader(gloomy::from_enum(kind)); return id; };
        static inline void release(const ID<Shader<kind>>& id) {
            assert(id.is_valid() && "Releasing null Shader.");
            gl::delete_shader(id.get());
        };
    };

    template<ShaderKind kind> struct CommittableTrait<Shader<kind>> {
        static inline void commit(const Shader<kind>& shader) {
            const auto& shader_source = shader.source.get();

            const char* c_source = shader_source.source.c_str();

            gl::shader_source(shader.get_raw_id(), 1, &c_source, nullptr);
            gl::compile_shader(shader.get_raw_id());

            {
                int32_t success;
                char info[512];
                gl::get_shader_iv(shader.get_raw_id(), gl::COMPILE_STATUS, &success);

                if (!success) {
                    gl::get_shader_info_log(shader.get_raw_id(), 512, nullptr, info);

                    assert(success && "Shader compilation failed.");
                }
            }
        };
    };

    template<ShaderKind kind>
    Shader<kind>::Shader(Shader&& other) noexcept
        : Object<Shader<kind>>(std::move(other.id)), source(std::move(other.source)) {
        other.id = gloomy::null_id<Shader<kind>>();
    }

    template<ShaderKind kind>
    Shader<kind>& gloomy::Shader<kind>::operator=(Shader&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->source = std::move(other.source);
            other.id = gloomy::null_id<Shader<kind>>();
        }

        return *this;
    }

    using VertexShader = Shader<gloomy::ShaderKind::VERTEX>;
    using FragmentShader = Shader<gloomy::ShaderKind::FRAGMENT>;
    using GeometryShader = Shader<gloomy::ShaderKind::GEOMETRY>;
}