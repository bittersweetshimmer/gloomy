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

namespace gloomy {
    template<ShaderKind Kind>
    struct Shader : public Object<Shader<Kind>>, public Committable<Shader<Kind>> {
        using Object<Shader<Kind>>::Object;

        Shader() : source(std::nullopt) {}
        Shader(const gloomy::src::Shader<Kind>& shader_source) : source(std::make_optional(std::ref(shader_source))) {};
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        constexpr static ShaderKind kind = Kind;

        std::optional<std::reference_wrapper<const gloomy::src::Shader<Kind>>> source;
    };

    template<ShaderKind Kind> struct ObjectTrait<Shader<Kind>> {
        static inline ID<Shader<Kind>> generate() {
            return ID<Shader<Kind>>(gl::create_shader(Kind));
        };
        static inline void release(const ID<Shader<Kind>>& id) {
            gl::delete_shader(id.get());
        };
    };

    template<ShaderKind Kind> struct CommittableTrait<Shader<Kind>> {
        static inline void commit(const Shader<Kind>& shader) {
            assert(shader.source.has_value() && "No source bound.");
            const auto& shader_source = shader.source.value().get();

            const char* c_source = shader_source.source.c_str();

            GLOOMY_CHECK(gl::raw::shader_source(shader.get_raw_id(), 1, &c_source, nullptr));
            GLOOMY_CHECK(gl::raw::compile_shader(shader.get_raw_id()));

            {
                int32_t success;
                char info[512];
                GLOOMY_CHECK(gl::raw::get_shader_iv(shader.get_raw_id(), gl::raw::COMPILE_STATUS, &success));

                if (!success) {
                    GLOOMY_CHECK(gl::raw::get_shader_info_log(shader.get_raw_id(), 512, nullptr, info));

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