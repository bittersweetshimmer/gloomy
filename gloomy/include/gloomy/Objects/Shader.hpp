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
    template<ShaderKind Kind>
    struct Shader : public Object<Shader<Kind>>, public Committable<Shader<Kind>> {
        using Object<Shader<Kind>>::Object;

        Shader() : source(gloomy::src::Shader<Kind>()) {}
        Shader(gloomy::src::Shader<Kind>&& shader_source) : source(std::move(shader_source)) {};
        Shader(const gloomy::src::Shader<Kind>& shader_source) : source(shader_source) {};
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        constexpr static ShaderKind kind = Kind;

        util::Cow<gloomy::src::Shader<Kind>> source;
    };

    template<ShaderKind Kind> struct ObjectTrait<Shader<Kind>> {
        static inline ID<Shader<Kind>> generate() { ID<Shader<Kind>> id;  GLOOMY_CHECK(id.get() = gl::create_shader(gloomy::from_enum(Kind))); return id; };
        static inline void release(const ID<Shader<Kind>>& id) {
            assert(id.is_valid() && "Releasing null Shader.");
            GLOOMY_CHECK(gl::delete_shader(id.get()));
        };
    };

    template<ShaderKind Kind> struct CommittableTrait<Shader<Kind>> {
        static inline void commit(const Shader<Kind>& shader) {
            const auto& shader_source = shader.source.get();

            const char* c_source = shader_source.source.c_str();

            GLOOMY_CHECK(gl::shader_source(shader.get_raw_id(), 1, &c_source, nullptr));
            GLOOMY_CHECK(gl::compile_shader(shader.get_raw_id()));

            {
                int32_t success;
                char info[512];
                GLOOMY_CHECK(gl::get_shader_iv(shader.get_raw_id(), gl::COMPILE_STATUS, &success));

                if (!success) {
                    GLOOMY_CHECK(gl::get_shader_info_log(shader.get_raw_id(), 512, nullptr, info));

                    assert(success && "Shader compilation failed.");
                }
            }
        };
    };

    template<ShaderKind Kind>
    Shader<Kind>::Shader(Shader&& other) noexcept
        : Object<Shader<Kind>>(std::move(other.id)), source(std::move(other.source)) {
        other.id = gloomy::null_id<Shader<Kind>>();
    }

    template<ShaderKind Kind>
    Shader<Kind>& gloomy::Shader<Kind>::operator=(Shader&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->source = std::move(other.source);
            other.id = gloomy::null_id<Shader<Kind>>();
        }

        return *this;
    }

    using VertexShader = Shader<gloomy::ShaderKind::VERTEX>;
    using FragmentShader = Shader<gloomy::ShaderKind::FRAGMENT>;
    using GeometryShader = Shader<gloomy::ShaderKind::GEOMETRY>;
}