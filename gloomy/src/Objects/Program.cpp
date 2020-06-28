#include <gloomy/Objects/Program.hpp>

gloomy::Program::Program(Program&& other) noexcept
    : Object(std::move(other.id)), shaders(std::move(other.shaders)), cached_locations(std::move(other.cached_locations)) {
}

gloomy::Program& gloomy::Program::operator=(Program&& other) noexcept {
    if (this != &other) {
        this->release();

        this->id = std::move(other.id);
        this->shaders = std::move(other.shaders);
        this->cached_locations = std::move(other.cached_locations);
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

const gloomy::Uniform& gloomy::Program::uniform(const std::string& name) const {
    auto found = this->cached_locations.find(name);
    if (found != this->cached_locations.end()) {
        return found->second;
    }
    else {
        this->cached_locations.insert({ name, gl::get_uniform(this->get_raw_id(), name) });
        return this->cached_locations.at(name);
    }
}
