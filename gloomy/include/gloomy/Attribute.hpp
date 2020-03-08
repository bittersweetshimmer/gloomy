#pragma once
#include <vector>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Type.hpp>
#include <gloomy/Utilities/Distinct.hpp>
#include <gloomy/Utilities/TypeList.hpp>

namespace gloomy {
    namespace priv {
        template <typename T>
        struct has_size {
        private:
            template <typename U>
            static constexpr decltype(std::declval<U>().size(), bool()) test_get(int) { return true; }

            template <typename U>
            static constexpr bool test_get(...) { return false; }

        public:
            static constexpr bool value = test_get<T>(int());
        };

        template <typename T>
        struct has_length {
        private:
            template <typename U>
            static constexpr decltype(std::declval<U>().length(), bool()) test_get(int) { return true; }

            template <typename U>
            static constexpr bool test_get(...) { return false; }

        public:
            static constexpr bool value = test_get<T>(int());
        };

        template <typename T>
        constexpr auto get_size_or_default() {
            if constexpr (has_size<T>::value) { return size_t{T().size()}; }
            else if constexpr (has_length<T>::value) { return size_t{T().length()}; }
            return size_t{0};
        }
    }

    template<typename T, Size L = priv::get_size_or_default<T>(), typename DT = typename T::value_type>
    struct AttributePadding final {
        using data_type = DT;
        
        static constexpr const Size size = sizeof(T);
        static constexpr const Size length = L;
        static constexpr const bool padding = true;
    };

    template<typename Tag, typename T, Size L = priv::get_size_or_default<T>(), bool Instanced = false, typename DT = typename T::value_type, bool Normalized = false>
    struct Attribute final : public util::Distinct<T, Tag> {
        using util::Distinct<T, Tag>::Distinct;

        using tag = Tag;
        using type = T;
        using data_type = DT;

        static constexpr const size_t size = sizeof(T);
        static constexpr const size_t data_size = sizeof(DT);
        static constexpr const size_t length = L;
        static constexpr const bool normalized = Normalized;
        static constexpr const bool instanced = Instanced;
        static constexpr const bool padding = false;

        static_assert(size > 16u ? size % 16u == 0 || size % 12u == 0 : true);

        using Pad = AttributePadding<T, L, DT>;
        using Instance = Attribute<Tag, T, L, true, DT, Normalized>;
    };

    struct DynamicAttribute final {
    public:
        Type type = gl_type<Float>();

        I32 length = 4u;
        size_t size = 16u;
        Size stride = 16u;
        IPointer offset = 0u;

        Bool instanced = false;
        Bool normalized = false;
        Bool padding = false;

        I32 part_length = 4u;
        I32 part_size = 16u;

        inline gloomy::U32 enable(gloomy::U32 index) const {
            if (this->padding) return index;
            
            for (size_t part_offset = 0; part_offset < this->size; part_offset += this->part_size) {
                GLOOMY_CHECK(gl::raw::enable_vertex_attrib_array(index));
                GLOOMY_CHECK(gl::raw::vertex_attrib_pointer(index,
                    this->part_length,
                    from_enum(this->type),
                    this->normalized,
                    this->stride,
                    reinterpret_cast<const void*>(this->offset + part_offset)
                ));

                if (this->instanced) {
                    GLOOMY_CHECK(gl::raw::vertex_attrib_divisor(index, 1));
                }

                index += 1;
            }

            return index;
        }
    };

    namespace priv {
        template<typename T, typename TList>
        constexpr auto attribute_offset(intptr_t acc = 0) {
            using Head = typename TList::Head;

            if constexpr (std::is_same_v<T, Head>) return acc;
            else {
                using Tail = typename TList::Tail;
                return attribute_offset<T, Tail>(acc + Head::size);
            }
        }

        template<typename Attr>
        DynamicAttribute make_attribute(GLsizei stride, intptr_t offset) {
            static_assert(Attr::size >= 1 && Attr::size <= 64);

            I32 part_length = Attr::length;
            I32 part_size = Attr::size;

            if (Attr::size > 16) {
                if (Attr::size % 16 == 0) { part_size = 16; }
                else if (Attr::size % 12 == 0) { part_size = 12; }
                part_length = Attr::size / part_size;
            }

            if constexpr (Attr::padding) {
                return DynamicAttribute{
                    .type = gl_type<typename Attr::data_type>(),
                    .length = Attr::length,
                    .size = Attr::size,
                    .stride = stride,
                    .offset = offset,
                    .instanced = false,
                    .normalized = false,
                    .padding = Attr::padding,
                    .part_length = part_length,
                    .part_size = part_size
                };
            }
            else {
                return DynamicAttribute{
                    .type = gl_type<typename Attr::data_type>(),
                    .length = Attr::length,
                    .size = Attr::size,
                    .stride = stride,
                    .offset = offset,
                    .instanced = Attr::instanced,
                    .normalized = Attr::normalized,
                    .padding = Attr::padding,
                    .part_length = part_length,
                    .part_size = part_size
                };
            }
        }

        template<typename AttrList, typename Attr, typename... Attrs>
        constexpr void make_attributes(std::vector<DynamicAttribute>& array, GLsizei stride, size_t position = 0) {
            array[position] = make_attribute<Attr>(stride, attribute_offset<Attr, AttrList>());

            if constexpr (sizeof...(Attrs) > 0) make_attributes<AttrList, Attrs...>(array, stride, position + 1);
        }
    }

    template<typename Attr, typename... Attrs>
    std::vector<DynamicAttribute> make_attributes() {
        constexpr auto stride = (Attr::size + ... + Attrs::size);
        constexpr auto length = 1 + sizeof...(Attrs);

        std::vector<DynamicAttribute> array(length);

        priv::template make_attributes<util::TypeList<Attr, Attrs...>, Attr, Attrs...>(array, stride);

        return array;
    }

    template<typename T, typename... Ts>
    struct Attributes : util::TypeList<T, Ts...> {
        static constexpr auto dynamic() { return make_attributes<T, Ts...>(); }
    };
}
