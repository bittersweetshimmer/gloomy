#pragma once
#include <vector>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Enum/Type.hpp>
#include <gloomy/Utilities/Distinct.hpp>
#include <gloomy/Utilities/TypeList.hpp>

namespace gloomy {
    template<typename Tag, typename T, typename DT = typename T::value_type, Size L = T().size(), bool Instanced = false, bool Normalized = false>
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
    };

    struct DynamicAttribute final {
    public:
        Type type = gl_type<Float>();

        I32 size = 4u;
        Size stride = 4u;
        IPointer offset = 0u;

        Bool instanced = false;
        Bool normalized = false;

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
        };

        template<typename Attr>
        DynamicAttribute make_attribute(GLsizei stride, intptr_t offset) {
            return DynamicAttribute{
                .type = gl_type<typename Attr::data_type>(),
                .size = Attr::length,
                .stride = stride,
                .offset = offset,
                .instanced = Attr::instanced,
                .normalized = Attr::normalized
            };
        };

        template<typename AttrList, typename Attr, typename... Attrs>
        constexpr void make_attributes(std::vector<DynamicAttribute>& array, GLsizei stride, size_t position = 0) {
            array[position] = make_attribute<Attr>(stride, attribute_offset<Attr, AttrList>());

            if constexpr (sizeof...(Attrs) > 0) make_attributes<AttrList, Attrs...>(array, stride, position + 1);
        };
    }

    template<typename Attr, typename... Attrs>
    std::vector<DynamicAttribute> make_attributes() {
        constexpr auto stride = (Attr::size + ... + Attrs::size);
        constexpr auto length = 1 + sizeof...(Attrs);

        std::vector<DynamicAttribute> array(length);

        priv::template make_attributes<util::TypeList<Attr, Attrs...>, Attr, Attrs...>(array, stride);

        return array;
    };

    template<typename T, typename... Ts>
    struct Attributes : util::TypeList<T, Ts...> {
        static constexpr auto dynamic() { return make_attributes<T, Ts...>(); }
    };
}
