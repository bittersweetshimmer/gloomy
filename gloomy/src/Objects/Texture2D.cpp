#include <gloomy/Objects/Texture2D.hpp>

gloomy::Texture2D::Texture2D(std::span<const std::byte> image) : image(image) {}
gloomy::Texture2D::Texture2D(gloomy::Texture2D &&other) noexcept
    : gloomy::Object<gloomy::Texture2D>(std::move(other.id)),
    image(std::move(other.image)),
    width(other.width),
    height(other.height),
    internal_format(other.internal_format),
    pixel_format(other.pixel_format),
    pixel_data_type(other.pixel_data_type) {
}

gloomy::Texture2D& gloomy::Texture2D::operator=(gloomy::Texture2D &&other) noexcept {
  if (this != &other) {
    this->release();

    this->id = std::move(other.id);
    this->image = std::move(other.image);
  }

  return *this;
}
