#pragma once
#include <type_traits>

namespace gloomy::util {
    template <typename T, typename Phantom>
    class Newtype {
    public:
        using underlying_type = T;
    private:
        underlying_type value = underlying_type();
    public:
        template<typename T, typename... Ts>
        constexpr Newtype(T&& argument, Ts&&... arguments) : value{ {std::forward<T>(argument), std::forward<Ts>(arguments)...} } {}

        explicit constexpr Newtype(const underlying_type& value) : value(value) {}
        explicit constexpr Newtype(underlying_type&& value) : value(std::move(value)) {}
        constexpr Newtype() : value(underlying_type()) {}
        constexpr underlying_type& get() { return value; }
        constexpr underlying_type const& get() const { return value; }

        operator underlying_type() { return value; }
        operator underlying_type() const { return value; }
    };
}