#pragma once
#include <optional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/Attribute.hpp>

namespace gloomy {
    struct VertexArray : public Object<VertexArray>, public Bindable<VertexArray>, public Committable<VertexArray> {
        using Object<VertexArray>::Object;

        template<typename... Attr>
        VertexArray(Attr... attributes) : attributes{ {attributes...} } {
            static_assert(std::conjunction_v<std::is_same_v<Attr, gloomy::DynamicAttribute>...>, "Variadic constructor accepts only DynamicAttributes.");
        };

        VertexArray(std::vector<gloomy::DynamicAttribute> attributes) : attributes(attributes) {}

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        template<typename... Attr>
        inline void set_attributes(Attr... attributes);
        inline void set_attributes(std::vector<gloomy::DynamicAttribute> attributes);
        inline const std::vector<gloomy::DynamicAttribute>& get_attributes();

    private:
        std::vector<gloomy::DynamicAttribute> attributes;

        friend typename Committable<VertexArray>::Trait;
    };

    template<> struct ObjectTrait<VertexArray> {
        static inline ID<VertexArray> generate() { ID<VertexArray> id; GLOOMY_CHECK(gl::raw::gen_vertex_arrays(1, &id.get())); return id; };
        static inline void release(const ID<VertexArray>& id) {
            assert(id.is_valid() && "Releasing null VertexArray.");
            GLOOMY_CHECK(gl::raw::delete_vertex_array(1, &id.get()));
        };
    };

    template<> struct BindableTrait<VertexArray> {
        static inline void bind(const VertexArray& va) {
            assert(va.get_id().is_valid() && "Binding not generated VertexArray.");
            GLOOMY_CHECK(gl::raw::bind_vertex_array(va.get_raw_id()));
        };
        static inline void unbind(const VertexArray& va) { GLOOMY_CHECK(gl::raw::bind_vertex_array(gloomy::null_raw_id)); };
    };

    template<> struct CommittableTrait<VertexArray> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const VertexArray& va) {

            auto attrib_index = 0;
            for (const auto& attribute : va.attributes) {
                for (auto part = 0; part < attribute.size; part += attribute.part_length()) {
                    if (attribute.padding) continue;
                     
                    GLOOMY_CHECK(gl::raw::enable_vertex_attrib_array(attrib_index));
                    GLOOMY_CHECK(gl::raw::vertex_attrib_pointer(attrib_index,
                        attribute.size,
                        from_enum(attribute.type),
                        attribute.normalized,
                        attribute.stride,
                        reinterpret_cast<const void*>(attribute.offset)
                    ));

                    if (attribute.instanced) {
                        GLOOMY_CHECK(gl::raw::vertex_attrib_divisor(attrib_index, 1));
                    }

                    attrib_index += 1;
                }
            }
        };
    };

    template<typename ...Attr>
    inline void VertexArray::set_attributes(Attr ...attributes) {
        this->attributes = { attributes... };
    }

    inline void VertexArray::set_attributes(std::vector<gloomy::DynamicAttribute> attributes) {
        this->attributes = attributes;
    }

    inline const std::vector<gloomy::DynamicAttribute>& gloomy::VertexArray::get_attributes() {
        return this->attributes;
    }
}