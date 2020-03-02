#include <gloomy/Objects/Framebuffer.hpp>

gloomy::Framebuffer::Framebuffer(Framebuffer&& other) noexcept
    : Object(std::move(other.id)), texture2d(std::move(other.texture2d)), renderbuffer(std::move(other.renderbuffer)) {
    other.id = gloomy::null_id<Framebuffer>();
}

gloomy::Framebuffer& gloomy::Framebuffer::operator=(Framebuffer&& other) noexcept {
    if (this != &other) {
        this->release();

        this->id = std::move(other.id);
        this->texture2d = std::move(other.texture2d);
        this->renderbuffer = std::move(other.renderbuffer);

        other.id = gloomy::null_id<Framebuffer>();
    }

    return *this;
}