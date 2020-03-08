#include <gloomy/Objects/Texture2D.hpp>

gloomy::Texture2D::Texture2D() : image(std::nullopt) {}
gloomy::Texture2D::Texture2D(const gloomy::src::Image &image) : image(std::make_optional(std::ref(image))){};
gloomy::Texture2D::Texture2D(gloomy::Texture2D &&other) noexcept
    : gloomy::Object<gloomy::Texture2D>(std::move(other.id)),
      image(std::move(other.image)) {
  other.id = gloomy::null_id<gloomy::Texture2D>();
}

gloomy::Texture2D& gloomy::Texture2D::operator=(gloomy::Texture2D &&other) noexcept {
  if (this != &other) {
    this->release();

    this->id = std::move(other.id);
    this->image = std::move(other.image);
    other.id = gloomy::null_id<gloomy::Texture2D>();
  }

  return *this;
}