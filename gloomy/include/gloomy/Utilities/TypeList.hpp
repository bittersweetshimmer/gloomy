#pragma once

namespace gloomy::util {
    template<typename T, typename R, typename... Rs>
    constexpr auto type_offset(size_t acc = 0) {
        if constexpr (std::is_same_v<T, R>) return acc;
        else return type_offset<T, Rs...>(acc + sizeof(R));
    };

    template<typename T, typename... Ts>
    struct TypeList {
        using Head = T;
        using Tail = TypeList<Ts...>;

        static constexpr auto length = sizeof...(Ts) + 1;

        template<template<typename...> typename TemplateT>
        using into = TemplateT<T, Ts...>;

        template<typename A>
        constexpr auto offset() { return type_offset<A, T, Ts...>(); }
    };

    template<typename T>
    struct TypeList<T> {
        using Head = T;

        static constexpr auto length = 1;

        template<template<typename> typename TemplateT>
        using into = TemplateT<T>;

        template<typename T>
        constexpr auto offset() { return 0; }
    };
}