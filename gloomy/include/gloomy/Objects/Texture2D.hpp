#pragma once
#include <optional>
#include <functional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Sources/Image.hpp>
#include <gloomy/Enum/Texture/Kind.hpp>
#include <gloomy/Utilities/CopyOnWrite.hpp>

namespace gloomy {
    template<Texture2DKind Kind = Texture2DKind::TEXTURE_2D>
    struct Texture2DLike : public Object<Texture2DLike<Kind>>, public Bindable<Texture2DLike<Kind>>, public Committable<Texture2DLike<Kind>> {
        using Object<Texture2DLike<Kind>>::Object;

        Texture2DLike() : source(gloomy::src::Image()) {}
        Texture2DLike(gloomy::src::Image&& image_source) : source(std::move(image_source)) {};
        Texture2DLike(const gloomy::src::Image& image_source) : source(image_source) {};
        Texture2DLike(Texture2DLike&& other) noexcept;
        Texture2DLike& operator=(Texture2DLike&& other) noexcept;

        constexpr static Texture2DKind kind = Kind;

        util::Cow<gloomy::src::Image> source;
    };

    template<Texture2DKind Kind> struct ObjectTrait<Texture2DLike<Kind>> {
        static inline ID<Texture2DLike<Kind>> generate() { ID<Texture2DLike<Kind>> id; GLOOMY_CHECK(gl::gen_textures(1, &id.get())); return id; };
        static inline void release(const ID<Texture2DLike<Kind>>& id) {
            assert(id.is_valid() && "Releasing null Texture2D.");
            GLOOMY_CHECK(gl::delete_textures(1, &id.get()));
        };
    };

    template<Texture2DKind Kind> struct BindableTrait<Texture2DLike<Kind>> {
        static inline void bind(const Texture2DLike<Kind>& texture) {
            assert(texture.get_id().is_valid() && "Binding not generated Texture2D.");
            GLOOMY_CHECK(gl::bind_texture(gloomy::from_enum(Kind), texture.get_raw_id())); 
        };
        static inline void unbind(const Texture2DLike<Kind>& texture) { GLOOMY_CHECK(gl::bind_texture(gloomy::from_enum(Kind), gloomy::null_raw_id)); };
    };

    template<Texture2DKind Kind> struct CommittableTrait<Texture2DLike<Kind>> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const Texture2DLike<Kind>& texture) {
            const gloomy::src::Image& image_source = texture.source.get();

			GLOOMY_CHECK(gl::tex_image_2D(
				gloomy::from_enum(Kind),
				0,
				from_enum(image_source.internal_format),
				image_source.width,
				image_source.height,
				0,
				from_enum(image_source.pixel_format),
				from_enum(image_source.pixel_data_type),
				image_source.pixels.data()
			));

            GLOOMY_CHECK(gl::tex_parameter_i(gloomy::from_enum(Kind), gl::TEXTURE_MIN_FILTER, gl::LINEAR));
			GLOOMY_CHECK(gl::tex_parameter_i(gloomy::from_enum(Kind), gl::TEXTURE_MAG_FILTER, gl::LINEAR));
        };
    };

    template<Texture2DKind Kind>
    Texture2DLike<Kind>::Texture2DLike(Texture2DLike&& other) noexcept
        : Object<Texture2DLike<Kind>>(std::move(other.id)), source(std::move(other.source)) {
        other.id = gloomy::null_id<Texture2DLike<Kind>>();
    }

    template<Texture2DKind Kind>
    Texture2DLike<Kind>& gloomy::Texture2DLike<Kind>::operator=(Texture2DLike&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->source = std::move(other.source);
            other.id = gloomy::null_id<Texture2DLike<Kind>>();
        }

        return *this;
    }

    using Texture2D = Texture2DLike<gloomy::Texture2DKind::TEXTURE_2D>;
}