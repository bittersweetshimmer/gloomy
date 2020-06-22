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
        template<typename... As, typename T1 = T, typename std::enable_if_t<std::is_aggregate_v<T1>>* = nullptr>
        constexpr Distinct(
            As&&... arguments
        ) : value{{
            std::forward<As>(arguments)...
        }} {}

        template<typename... As, typename T1 = T, typename std::enable_if_t<!std::is_aggregate_v<T1>>* = nullptr>
        constexpr Distinct(
            As&&... arguments
        ) : value(
            std::forward<As>(arguments)...
        ) {}

        explicit constexpr Distinct(const underlying_type& value) : value(value) {}
        explicit constexpr Distinct(underlying_type&& value) : value(std::move(value)) {}
        
        constexpr Distinct() : value(underlying_type()) {}
        constexpr Distinct(const Distinct& other) : value(other.value) {}
        
        inline Distinct& operator=(const Distinct& other) {
            this->value = other.value;
            return *this;
        }
        constexpr Distinct(Distinct&& other) : value(std::move(other.value)) {}
        inline Distinct& operator=(Distinct&& other) {
            this->value = std::move(other.value);
            return *this;
        }

        constexpr underlying_type& get() { return value; }
        constexpr underlying_type const& get() const { return value; }

        operator underlying_type() { return value; }
        operator underlying_type() const { return value; }
    };
}