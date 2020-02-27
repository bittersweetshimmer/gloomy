#pragma once
#include <functional>
#include <optional>

#include <gloomy/Enum/Texture/Target.hpp>
#include <gloomy/GL/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/Sources/Image.hpp>
#include <gloomy/gl.hpp>

namespace gloomy {
struct Texture2D : public Object<Texture2D>,
                       public Bindable<Texture2D>,
                       public Committable<Texture2D> {
  using Object<Texture2D>::Object;

  Texture2D() : image(std::nullopt) {}
  Texture2D(const gloomy::src::Image &image)
      : image(std::make_optional(std::ref(image))){};
  Texture2D(Texture2D &&other) noexcept;
  Texture2D &operator=(Texture2D &&other) noexcept;

  std::optional<std::reference_wrapper<const gloomy::src::Image>> image;

  inline void bind_at_slot(size_t index) const { gl::bind_texture_at_slot(TextureTarget::TEXTURE_2D, this->get_raw_id(), index); }
};

template <> struct ObjectTrait<Texture2D> {
  static inline ID<Texture2D> generate() {
    return ID<Texture2D>(gl::gen_texture());
  };
  static inline void release(const ID<Texture2D> &id) {
    gl::delete_texture(id.get());
  };
};

template <> struct BindableTrait<Texture2D> {
  static inline void bind(const Texture2D &texture) {
    gl::bind_texture(TextureTarget::TEXTURE_2D, texture.get_raw_id());
  };
  static inline void unbind(const Texture2D &) {
    gl::unbind_texture(TextureTarget::TEXTURE_2D);
  };
};

template <> struct CommittableTrait<Texture2D> {
  static constexpr bool bind_before_commit = true;
  static inline void commit(const Texture2D &texture) {
    assert(texture.image.has_value() && "No image bound.");
    const gloomy::src::Image &image = texture.image.value().get();

    GLOOMY_CHECK(gl::raw::tex_image_2D(
        gloomy::from_enum(Texture2DKind::TEXTURE_2D), 0, from_enum(image.internal_format),
        image.width, image.height, 0,
        from_enum(image.pixel_format),
        from_enum(image.pixel_data_type), image.data.get()));

    GLOOMY_CHECK(gl::raw::tex_parameter_i(gloomy::from_enum(TextureTarget::TEXTURE_2D),
                                          gl::raw::TEXTURE_MIN_FILTER, gl::raw::LINEAR));
    GLOOMY_CHECK(gl::raw::tex_parameter_i(gloomy::from_enum(TextureTarget::TEXTURE_2D),
                                          gl::raw::TEXTURE_MAG_FILTER, gl::raw::LINEAR));
  };
};

Texture2D::Texture2D(Texture2D &&other) noexcept
    : Object<Texture2D>(std::move(other.id)),
      image(std::move(other.image)) {
  other.id = gloomy::null_id<Texture2D>();
}

Texture2D& gloomy::Texture2D::operator=(Texture2D &&other) noexcept {
  if (this != &other) {
    this->release();

    this->id = std::move(other.id);
    this->image = std::move(other.image);
    other.id = gloomy::null_id<Texture2D>();
  }

  return *this;
}

} // namespace gloomy
