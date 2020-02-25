#include <glm/glm.hpp>
#include <gloomy/Attribute.hpp>

namespace learnopengl {
    using Position = gloomy::Attribute<struct PositionTag, glm::vec3>;
    using TextureCoord = gloomy::Attribute<struct TextureCoordTag, glm::vec2>;

    using Attributes = gloomy::Attributes<Position, TextureCoord>;
    using Vertex = gloomy::Vertex<Position, TextureCoord>;
}