#include <gloomy/Objects/Renderbuffer.hpp>

gloomy::Renderbuffer::Renderbuffer(Renderbuffer&& other) noexcept
    : Object(std::move(other.id)), width(other.width), height(other.height), format(std::move(other.format)) {
    other.id = gloomy::null_id<Renderbuffer>();
}

gloomy::Renderbuffer& gloomy::Renderbuffer::operator=(Renderbuffer&& other) noexcept {
    if (this != &other) {
        this->release();

        this->id = std::move(other.id);
        this->format = std::move(other.format);
        this->width = other.width;
        this->height = other.height;

        other.id = gloomy::null_id<Renderbuffer>();
    }

    return *this;
}