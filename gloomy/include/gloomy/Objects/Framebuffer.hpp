#pragma once
#include <optional>
#include <unordered_map>
#include <functional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/API.hpp>

#include <gloomy/Enum/Framebuffer/Target.hpp>
#include <gloomy/Enum/Framebuffer/Attachment.hpp>
#include <gloomy/Enum/Framebuffer/TextureTarget.hpp>

namespace gloomy {
    struct Framebuffer : public Object<Framebuffer>, public Bindable<Framebuffer>, public Committable<Framebuffer> {
        using Object<Framebuffer>::Object;

        Framebuffer(Framebuffer&& other) noexcept;
        Framebuffer& operator=(Framebuffer&& other) noexcept;

        inline void attach_texture2d(const gloomy::AnyObject& attachment) { this->texture2d = std::ref(attachment); } 
        inline void attach_renderbuffer(const gloomy::AnyObject& attachment) { this->renderbuffer = std::ref(attachment); } 
    
    private:
        std::reference_wrapper<const gloomy::AnyObject> texture2d;
        std::reference_wrapper<const gloomy::AnyObject> renderbuffer;
        friend struct CommittableTrait<Framebuffer>;
    };

    template<> struct ObjectTrait<Framebuffer> {
        static inline ID<Framebuffer> generate() {
            return ID<Framebuffer>(gl::gen_framebuffer());
        };
        static inline void release(const ID<Framebuffer>& id) {
            gl::delete_framebuffer(id);
        };
    };

    template<> struct BindableTrait<Framebuffer> {
        static inline void bind(const Framebuffer& framebuffer) {
            gl::bind_framebuffer(gloomy::FramebufferTarget::FRAMEBUFFER, framebuffer.get_raw_id());
        };
        static inline void unbind(const Framebuffer&) {
            gl::unbind_framebuffer(gloomy::FramebufferTarget::FRAMEBUFFER);
        };
    };

    template<> struct CommittableTrait<Framebuffer> {
        static constexpr bool bind_before_commit = false;
        static inline void commit(const Framebuffer& framebuffer) {
            gl::framebuffer_texture2d(
                gloomy::FramebufferTarget::FRAMEBUFFER,
                gloomy::FramebufferAttachment::COLOR_ATTACHMENT0,
                gloomy::FramebufferTextureTarget::TEXTURE_2D,
                framebuffer.texture2d.get().get_raw_id()
            );

            gl::framebuffer_renderbuffer(
                gloomy::FramebufferTarget::FRAMEBUFFER,
                gloomy::FramebufferAttachment::DEPTH_STENCIL_ATTACHMENT,
                gloomy::RenderbufferTarget::RENDERBUFFER,
                framebuffer.renderbuffer.get().get_raw_id()
            );
        };
    };
}