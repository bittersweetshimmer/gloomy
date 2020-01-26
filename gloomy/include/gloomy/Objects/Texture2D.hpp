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
    template<Texture2DKind kind = Texture2DKind::TEXTURE_2D>
    struct Texture2DLike : public Object<Texture2DLike<kind>>, public Bindable<Texture2DLike<kind>>, public Committable<Texture2DLike<kind>> {
        using Object<Texture2DLike<kind>>::Object;

        Texture2DLike() : source(gloomy::src::Image()) {}
        Texture2DLike(gloomy::src::Image&& image_source) : source(std::move(image_source)) {};
        Texture2DLike(const gloomy::src::Image& image_source) : source(image_source) {};
        Texture2DLike(Texture2DLike&& other) noexcept;
        Texture2DLike& operator=(Texture2DLike&& other) noexcept;

        constexpr static Texture2DKind kind = kind;

        util::Cow<gloomy::src::Image> source;
    };

    template<Texture2DKind kind> struct ObjectTrait<Texture2DLike<kind>> {
        static inline ID<Texture2DLike<kind>> generate() { ID<Texture2DLike<kind>> id; gl::gen_textures(1, &id.get()); return id; };
        static inline void release(const ID<Texture2DLike<kind>>& id) {
            assert(id.is_valid() && "Releasing null Texture2D.");
            gl::delete_textures(1, &id.get());
        };
    };

    template<Texture2DKind kind> struct BindableTrait<Texture2DLike<kind>> {
        static inline void bind(const Texture2DLike<kind>& texture) {
            assert(texture.get_id().is_valid() && "Binding not generated Texture2D.");
            gl::bind_texture(gloomy::from_enum(kind), texture.get_raw_id()); 
        };
        static inline void unbind(const Texture2DLike<kind>& texture) { gl::bind_texture(gloomy::from_enum(kind), gloomy::null_raw_id); };
    };

    template<Texture2DKind kind> struct CommittableTrait<Texture2DLike<kind>> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const Texture2DLike<kind>& texture) {
            const gloomy::src::Image& image_source = texture.source.get();

			gl::tex_image_2D(
				gloomy::from_enum(kind),
				0,
				from_enum(image_source.internal_format),
				image_source.width,
				image_source.height,
				0,
				from_enum(image_source.pixel_format),
				from_enum(image_source.pixel_data_type),
				image_source.pixels.data()
			);

		    gl::tex_parameter_i(gloomy::from_enum(kind), gl::TEXTURE_MIN_FILTER, gl::LINEAR);
			gl::tex_parameter_i(gloomy::from_enum(kind), gl::TEXTURE_MAG_FILTER, gl::LINEAR);
        };
    };

    template<Texture2DKind kind>
    Texture2DLike<kind>::Texture2DLike(Texture2DLike&& other) noexcept
        : Object<Texture2DLike<kind>>(std::move(other.id)), source(std::move(other.source)) {
        other.id = gloomy::null_id<Texture2DLike<kind>>();
    }

    template<Texture2DKind kind>
    Texture2DLike<kind>& gloomy::Texture2DLike<kind>::operator=(Texture2DLike&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->source = std::move(other.source);
            other.id = gloomy::null_id<Texture2DLike<kind>>();
        }

        return *this;
    }

    using Texture2D = Texture2DLike<gloomy::Texture2DKind::TEXTURE_2D>;
}