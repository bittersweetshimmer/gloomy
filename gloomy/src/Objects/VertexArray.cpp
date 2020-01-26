#include <gloomy/Objects/VertexArray.hpp>

gloomy::VertexArray::VertexArray(VertexArray&& other) noexcept
	: Object(std::move(other.id)), attributes(std::move(other.attributes)) {
	other.id = gloomy::null_id<VertexArray>();
}

gloomy::VertexArray& gloomy::VertexArray::operator=(VertexArray&& other) noexcept {
    if (this != &other) {
        this->release();

        this->id = std::move(other.id);
        this->attributes = std::move(other.attributes);

        other.id = gloomy::null_id<VertexArray>();
    }

    return *this;
}