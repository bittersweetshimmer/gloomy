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

        VertexArray(std::vector<gloomy::DynamicAttribute>&& attributes) : attributes(std::move(attributes)) {}

        VertexArray(VertexArray&& other) noexcept;
        VertexArray& operator=(VertexArray&& other) noexcept;

        inline void enable_dynamic_attributes(const std::vector<gloomy::DynamicAttribute>& attributes);

        template<typename T>
        inline void enable_attributes();

        inline const std::vector<gloomy::DynamicAttribute>& get_attributes() const;
    private:
        std::vector<gloomy::DynamicAttribute> attributes;
        mutable size_t current_enabled = 0;
        mutable gloomy::U32 current_attribute_index = 0;

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
        static inline void unbind(const VertexArray&) { GLOOMY_CHECK(gl::raw::bind_vertex_array(gloomy::null_raw_id)); };
    };

    template<> struct CommittableTrait<VertexArray> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const VertexArray& va) {
            for (auto i = va.current_enabled; i < va.attributes.size(); ++i) {
                const auto& attribute = va.attributes[i];

                va.current_attribute_index = attribute.enable(va.current_attribute_index);
            }

            va.current_enabled = va.attributes.size();
        };
    };

    inline void VertexArray::enable_dynamic_attributes(const std::vector<gloomy::DynamicAttribute>& new_attributes) {
        this->attributes.insert(this->attributes.end(), new_attributes.begin(), new_attributes.end());

        this->commit();
    }

    template<typename T>
    inline void VertexArray::enable_attributes() {
        const auto dynamic = T::dynamic();
        this->attributes.insert(this->attributes.end(), dynamic.begin(), dynamic.end());

        this->commit();
    }

    inline const std::vector<gloomy::DynamicAttribute>& VertexArray::get_attributes() const { return this->attributes; }
}
