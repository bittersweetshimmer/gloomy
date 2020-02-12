#pragma once
#include <type_traits>

namespace gloomy::util {
    template <typename T, typename Phantom>
    class Distinct {
    public:
        using underlying_type = T;
    private:
        underlying_type value = underlying_type();
    public:
        template<typename A, typename... As>
        constexpr Distinct(A&& argument, As&&... arguments) : value{ {std::forward<A>(argument), std::forward<As>(arguments)...} } {}

        explicit constexpr Distinct(const underlying_type& value) : value(value) {}
        explicit constexpr Distinct(underlying_type&& value) : value(std::move(value)) {}
        constexpr Distinct() : value(underlying_type()) {}
        constexpr underlying_type& get() { return value; }
        constexpr underlying_type const& get() const { return value; }

        operator underlying_type() { return value; }
        operator underlying_type() const { return value; }
    };
}