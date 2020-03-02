#pragma once
#include <optional>
#include <unordered_map>
#include <functional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/API.hpp>

#include <gloomy/Enum/Renderbuffer/Target.hpp>
#include <gloomy/Enum/Renderbuffer/InternalFormat.hpp>

namespace gloomy {
    struct Renderbuffer : public Object<Renderbuffer>, public Bindable<Renderbuffer>, public Committable<Renderbuffer> {
        using Object<Renderbuffer>::Object;

        Renderbuffer(gloomy::U32 width, gloomy::U32 height, gloomy::RenderbufferInternalFormat format = gloomy::RenderbufferInternalFormat::DEPTH24_STENCIL8)
            : width(width), height(height), format(format) {}

        Renderbuffer(Renderbuffer&& other) noexcept;
        Renderbuffer& operator=(Renderbuffer&& other) noexcept;

        gloomy::U32 width = 0;
        gloomy::U32 height = 0;
        gloomy::RenderbufferInternalFormat format = gloomy::RenderbufferInternalFormat::DEPTH24_STENCIL8;
    private:
        friend struct CommittableTrait<Renderbuffer>;
    };

    template<> struct ObjectTrait<Renderbuffer> {
        static inline ID<Renderbuffer> generate() {
            return ID<Renderbuffer>(gl::gen_renderbuffer());
        };
        static inline void release(const ID<Renderbuffer>& id) {
            gl::delete_renderbuffer(id);
        };
    };

    template<> struct BindableTrait<Renderbuffer> {
        static inline void bind(const Renderbuffer& renderbuffer) {
            gl::bind_renderbuffer(gloomy::RenderbufferTarget::RENDERBUFFER, renderbuffer.get_raw_id());
        };
        static inline void unbind(const Renderbuffer&) {
            gl::unbind_renderbuffer(gloomy::RenderbufferTarget::RENDERBUFFER);
        };
    };

    template<> struct CommittableTrait<Renderbuffer> {
        static constexpr bool bind_before_commit = false;
        static inline void commit(const Renderbuffer& renderbuffer) {
            gl::renderbuffer_storage(gloomy::RenderbufferTarget::RENDERBUFFER, renderbuffer.format, renderbuffer.width, renderbuffer.height);
        };
    };
}