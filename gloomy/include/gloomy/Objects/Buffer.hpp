#pragma once
#include <optional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Enum/Buffer/Usage.hpp>
#include <gloomy/Enum/Buffer/Kind.hpp>
#include <gloomy/Sources/BufferView.hpp>

namespace gloomy {
    template<BufferKind Kind>
    struct Buffer : public Object<Buffer<Kind>>, public Bindable<Buffer<Kind>>, public Committable<Buffer<Kind>> {
        using Object<Buffer<Kind>>::Object;

        template<typename T>
        Buffer(const T& container, BufferUsage usage = BufferUsage::from(BufferUsageCombined::STATIC_DRAW)) : view(src::BufferView::from(container)), usage(usage) {};

        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;

        BufferUsage usage = BufferUsage::from(BufferUsageCombined::STATIC_DRAW);
        src::BufferView view;

        constexpr static BufferKind kind = Kind;
        friend struct Committable<Buffer>::Trait;
    };

    template<BufferKind Kind> struct ObjectTrait<Buffer<Kind>> {
        static inline ID<Buffer<Kind>> generate() {
            return ID<Buffer<Kind>>(gl::gen_buffer());
        };
        static inline void release(const ID<Buffer<Kind>>& id) {
            gl::delete_buffer(id);
        };
    };

    template<BufferKind Kind> struct BindableTrait<Buffer<Kind>> {
        static inline void bind(const Buffer<Kind>& buffer) {
            gl::bind_buffer(Kind, buffer.get_raw_id());
        };
        static inline void unbind(const Buffer<Kind>& buffer) {
            gl::unbind_buffer(Kind);
        };
    };

    template<BufferKind Kind> struct CommittableTrait<Buffer<Kind>> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const Buffer<Kind>& buffer) {
            gl::buffer_data(Kind, buffer.view, buffer.usage);
        };
    };

    template<BufferKind Kind>
    Buffer<Kind>::Buffer(Buffer&& other) noexcept
        : Object<Buffer<Kind>>(std::move(other.id)), usage(other.usage), view(std::move(other.view)) {
        other.id = gloomy::null_id<Buffer<Kind>>();
    }

    template<BufferKind Kind>
    Buffer<Kind>& gloomy::Buffer<Kind>::operator=(Buffer&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->usage = other.usage;
            this->view = std::move(other.view);

            other.id = gloomy::null_id<Buffer<Kind>>();
        }

        return *this;
    }

    using VertexBuffer = Buffer<gloomy::BufferKind::ARRAY_BUFFER>;
    using IndexBuffer = Buffer<gloomy::BufferKind::ELEMENT_ARRAY_BUFFER>;
    using QueryBuffer = Buffer<gloomy::BufferKind::QUERY_BUFFER>;
}