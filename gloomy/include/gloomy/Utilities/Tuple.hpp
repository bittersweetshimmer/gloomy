#pragma once
#include <cstddef>
#include <array>
#include <type_traits>
#include <gloomy/Utilities/TypeList.hpp>

namespace gloomy::util {
    template<typename A, typename... As>
    struct Tuple final : public TypeList<A, As...> {
    private:
        constexpr static size_t size = (sizeof(A) + ... + sizeof(As));
        using Block = std::array<std::byte, size>;

        Block block;

    public:
        Tuple() : block{} {};
        Tuple(A value, As... values) : block{} {
            this->assign(value, values...);
        }

        template<typename... Ts>
        constexpr static Tuple<A, As...> from(Ts... values) {
            Tuple<A, As...> tuple;

            tuple.assign(values...);

            return tuple;
        }

        template<typename T>
        T& get() {
            return *reinterpret_cast<T*>(this->block.data() + type_offset<T, A, As...>());
        }

        template<typename T>
        const T& get() const {
            return *reinterpret_cast<const T*>(this->block.data() + type_offset<T, A, As...>());
        }

        template<typename T, typename... Ts>
        constexpr void assign(T value, Ts... values) {
            this->get<T>() = value;

            if constexpr (sizeof...(Ts) > 0) this->assign(values...);
        }
    };
}
