#include <gloomy/Objects/Program.hpp>

gloomy::Program::Program(Program&& other) noexcept
    : Object(std::move(other.id)), shaders(std::move(other.shaders)) {
    other.id = gloomy::null_id<Program>();
}

gloomy::Program& gloomy::Program::operator=(Program&& other) noexcept {
    if (this != &other) {
        this->release();

        this->id = std::move(other.id);
        this->shaders = std::move(other.shaders);

        other.id = gloomy::null_id<Program>();
    }

    return *this;
}

inline std::vector<gloomy::RawID>& gloomy::Program::get_shaders() {
    return this->shaders;
}

inline const std::vector<gloomy::RawID>& gloomy::Program::get_shaders() const {
    return this->shaders;
}

inline void gloomy::Program::clear_shaders() {
    this->shaders.clear();
}

/*
gloomy::Program::UniformLocation gloomy::Program::get_uniform_location(const std::string& name) const {
    auto found = this->cached_locations.find(name);
    if (found != this->cached_locations.end()) {
        return found->second;
    }
    else {
        auto location = gl::get_uniform_location(this->get_raw_id(), name.c_str());

        this->cached_locations.insert({ name, location });

        return location;
    }
}
*/