#pragma once

#include <gloomy/gl.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Utilities/Distinct.hpp>
#include <gloomy/Utilities/NonCopyable.hpp>

namespace gloomy {
    using RawID = U32;
    constexpr RawID null_raw_id = 0;

    template<typename T>
    struct ID : util::Distinct<RawID, T>, util::NonCopyable {
        ID() : util::Distinct<RawID, T>(null_raw_id) {};
        ID(RawID raw) : util::Distinct<RawID, T>(raw) {};
        ID(ID&& other) : util::Distinct<RawID, T>(other.get()) { other.get() = null_raw_id; }
        ID& operator=(ID&& other) { this->get() = other.get(); other.get() = null_raw_id; return *this; }

        constexpr auto is_valid() const -> bool { return this->get() != null_raw_id; }
        constexpr auto is_null() const -> bool { return !this->is_valid(); }
    };

    template<typename T>
    ID<T> null_id() { return ID<T>(null_raw_id); }
}
