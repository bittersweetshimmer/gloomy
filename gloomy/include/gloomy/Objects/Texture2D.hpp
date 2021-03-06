#pragma once
#include <span>
#include <functional>
#include <optional>

#include <gloomy/Utilities/ByteSpan.hpp>
#include <gloomy/Enum/Texture/Target.hpp>
#include <gloomy/GL/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/Enum/Texture/InternalFormat.hpp>
#include <gloomy/Enum/Texture/PixelFormat.hpp>
#include <gloomy/Enum/Texture/PixelDataType.hpp>
#include <gloomy/gl.hpp>

namespace gloomy {
    struct Texture2D : public Object<Texture2D>,
    public Bindable<Texture2D>,
    public Committable<Texture2D> {
        using Object<Texture2D>::Object;

        template<typename T>
        Texture2D(const T* data, std::size_t size, gloomy::Size width, gloomy::Size height) : image(gloomy::util::as_bytes(data, size)), width(width), height(height) {}
        Texture2D(std::span<const std::byte> image, gloomy::Size width, gloomy::Size height);
        Texture2D(Texture2D &&other) noexcept;
        Texture2D &operator=(Texture2D &&other) noexcept;

        std::span<const std::byte> image;
        gloomy::Size width = 0;
        gloomy::Size height = 0;
        gloomy::TextureInternalFormat internal_format = gloomy::TextureInternalFormat::RGBA;
        gloomy::PixelFormat pixel_format = gloomy::PixelFormat::RGBA;
        gloomy::PixelDataType pixel_data_type = gloomy::PixelDataType::U8;
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
            GLOOMY_CHECK(gl::raw::tex_image_2D(
                gloomy::from_enum(Texture2DKind::TEXTURE_2D), 0, from_enum(texture.internal_format),
                texture.width, texture.height, 0,
                from_enum(texture.pixel_format),
                from_enum(texture.pixel_data_type), texture.image.data()
            ));

            GLOOMY_CHECK(gl::raw::tex_parameter_i(gloomy::from_enum(TextureTarget::TEXTURE_2D),
                        gl::raw::TEXTURE_MIN_FILTER, gl::raw::NEAREST));
            GLOOMY_CHECK(gl::raw::tex_parameter_i(gloomy::from_enum(TextureTarget::TEXTURE_2D),
                        gl::raw::TEXTURE_MAG_FILTER, gl::raw::NEAREST));

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        };
    };

} // namespace gloomy
