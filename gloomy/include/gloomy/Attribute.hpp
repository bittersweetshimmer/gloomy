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

    template<typename Tag, typename T, Size L = priv::get_size_or_default<T>(), typename DT = typename T::value_type, bool Instanced = false, bool Normalized = false>
    struct Attribute final : public util::Distinct<T, Tag> {
        using util::Distinct<T, Tag>::Distinct;

        using tag = Tag;
        using type = T;
        using data_type = DT;

        static constexpr const Size size = sizeof(T);
        static constexpr const Size data_size = sizeof(DT);
        static constexpr const Size length = L;
        static constexpr const bool normalized = Normalized;
        static constexpr const bool instanced = Instanced;
        static constexpr const bool padding = false;

        using Pad = AttributePadding<T, L, DT>;
    };

    struct DynamicAttribute final {
    public:
        Type type = gl_type<Float>();

        I32 size = 4u;
        Size stride = 4u;
        IPointer offset = 0u;

        Bool instanced = false;
        Bool normalized = false;
        Bool padding = false;

        constexpr auto part_length() const {
            return this->size % 4 == 0 ? 4 :
                this->size % 3 == 0 ? 3 :
                this->size % 2 == 0 ? 2 : 1;
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
            if constexpr (Attr::padding) {
                return DynamicAttribute{
                    .type = gl_type<typename Attr::data_type>(),
                    .size = Attr::length,
                    .stride = stride,
                    .offset = offset,
                    .instanced = false,
                    .normalized = false,
                    .padding = Attr::padding
                };
            }
            else {
                return DynamicAttribute{
                    .type = gl_type<typename Attr::data_type>(),
                    .size = Attr::length,
                    .stride = stride,
                    .offset = offset,
                    .instanced = Attr::instanced,
                    .normalized = Attr::normalized,
                    .padding = Attr::padding
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
