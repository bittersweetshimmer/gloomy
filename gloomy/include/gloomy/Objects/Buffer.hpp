#pragma once
#include <optional>

#include <gloomy/gl.hpp>
#include <gloomy/Objects/Bindable.hpp>
#include <gloomy/Objects/Committable.hpp>
#include <gloomy/Objects/Object.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/GL/Raw/Enum.hpp>
#include <gloomy/Utilities/CopyOnWrite.hpp>
#include <gloomy/Utilities/Span.hpp>
#include <gloomy/Utilities/DynamicArray.hpp>
#include <gloomy/Enum/Buffer/Usage.hpp>
#include <gloomy/Enum/Buffer/Kind.hpp>

namespace gloomy {
    template<BufferKind Kind>
    struct Buffer : public Object<Buffer<Kind>>, public Bindable<Buffer<Kind>>, public Committable<Buffer<Kind>> {
        using Object<Buffer<Kind>>::Object;

        template<typename T>
        Buffer(const T& bytes, BufferUsage usage = BufferUsage::from(BufferUsageCombined::STATIC_DRAW)) : source(util::as_byte_span(bytes)), usage(usage) {};

        Buffer(Buffer&& other) noexcept;
        Buffer& operator=(Buffer&& other) noexcept;

        BufferUsage usage = BufferUsage::from(BufferUsageCombined::STATIC_DRAW);
        util::ByteSpan source;

        constexpr static BufferKind kind = Kind;
        friend struct Committable<Buffer>::Trait;
    };

    template<BufferKind Kind> struct ObjectTrait<Buffer<Kind>> {
        static inline ID<Buffer<Kind>> generate() { ID<Buffer<Kind>> id; gl::gen_buffers(1, &id.get()); return id; };
        static inline void release(const ID<Buffer<Kind>>& id) {
            assert(id.is_valid() && "Releasing null Buffer.");
            gl::delete_buffers(1, &id.get());
        };
    };

    template<BufferKind Kind> struct BindableTrait<Buffer<Kind>> {
        static inline void bind(const Buffer<Kind>& buffer) {
            assert(buffer.get_id().is_valid() && "Binding not generated Buffer.");
            gl::bind_buffer(gloomy::from_enum(Kind), buffer.get_raw_id());
        };
        static inline void unbind(const Buffer<Kind>& buffer) { gl::bind_buffer(gloomy::from_enum(Kind), gloomy::null_raw_id); };
    };

    template<BufferKind Kind> struct CommittableTrait<Buffer<Kind>> {
        static constexpr bool bind_before_commit = true;
        static inline void commit(const Buffer<Kind>& buffer) {
            const auto& bytes = buffer.source;

            gl::buffer_data(gloomy::from_enum(Kind), bytes.size(), bytes.data(), gloomy::from_enum(buffer.usage.combined()));
        };
    };

    template<BufferKind Kind>
    Buffer<Kind>::Buffer(Buffer&& other) noexcept
        : Object<Buffer<Kind>>(std::move(other.id)), usage(other.usage), source(std::move(other.source)) {
        other.id = gloomy::null_id<Buffer<Kind>>();
    }

    template<BufferKind Kind>
    Buffer<Kind>& gloomy::Buffer<Kind>::operator=(Buffer&& other) noexcept {
        if (this != &other) {
            this->release();

            this->id = std::move(other.id);
            this->usage = other.usage;
            this->source = std::move(other.source);

            other.id = gloomy::null_id<Buffer<Kind>>();
        }

        return *this;
    }

    using VertexBuffer = Buffer<gloomy::BufferKind::ARRAY_BUFFER>;
    using IndexBuffer = Buffer<gloomy::BufferKind::ELEMENT_ARRAY_BUFFER>;
    using QueryBuffer = Buffer<gloomy::BufferKind::QUERY_BUFFER>;
}