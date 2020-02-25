#pragma once
#include <string>

#include <gloomy/Objects/UniformLocation.hpp>
#include <gloomy/TypeAliases.hpp>
#include <gloomy/Utilities/Distinct.hpp>
#include <gloomy/GL/Raw/API.hpp>
#include <gloomy/Objects/ID.hpp>

namespace gloomy {
    struct Uniform {
        explicit Uniform(UniformLocation location, std::string name, gloomy::RawID id) : _location(location), _name(name), _id(id) {};

        const UniformLocation& location() const;
        const std::string& name() const;
        const gloomy::RawID& program_id() const;

        template<typename T, size_t M = 1, size_t N = 1>
        inline void set(const T* value, gloomy::Size count = 1, gloomy::Bool transpose = false) const {
            gl::set_uniform<T, M, N>(this->_location, value, count, transpose);
        };

        template<typename T, size_t M>
        inline void vec(const T* value, gloomy::Size count = 1) const {
            gl::set_uniform_vec<T, M>(this->_location, value, count);
        };

        template<size_t M>
        inline void fvec(const gloomy::Float* value, gloomy::Size count = 1) const {
            gl::set_uniform_vec<gloomy::Float, M>(this->_location, value, count);
        };

        template<size_t M>
        inline void ivec(const gloomy::I32* value, gloomy::Size count = 1) const {
            gl::set_uniform_vec<gloomy::I32, M>(this->_location, value, count);
        };

        template<size_t M>
        inline void uivec(const gloomy::U32* value, gloomy::Size count = 1) const {
            gl::set_uniform_vec<gloomy::U32, M>(this->_location, value, count);
        };

        template<typename T, typename... Ts>
        inline void values(Ts&&... values) const {
            gl::set_uniform_by_values<T>(this->_location, std::forward<Ts>(values)...);
        };

        template<size_t M, size_t N = M>
        inline void matrix(const gloomy::Float* value, gloomy::Size count = 1, gloomy::Bool transpose = false) const {
            gl::set_uniform<gloomy::Float, M, N>(this->_location, value, count, transpose);
        };

        inline void sampler(size_t index) const {
            gl::set_uniform_by_values<gloomy::I32>(this->_location, static_cast<gloomy::I32>(index));
        };

    private:
        UniformLocation _location;
        std::string _name;
        gloomy::RawID _id;
    };

    namespace gl {
        inline Uniform get_uniform(gloomy::RawID program, const std::string& name) {
            auto location = gl::get_uniform_location(program, name.c_str());

            return Uniform(location, name, program);
        };
    }
}