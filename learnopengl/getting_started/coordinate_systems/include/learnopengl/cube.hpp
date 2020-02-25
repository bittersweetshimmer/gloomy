#include <array>
#include <learnopengl/types.hpp>

namespace learnopengl {
    auto make_cube() {
        return std::array<Vertex, 36>{
            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position( 0.5f, -0.5f, -0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position( 0.5f,  0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position( 0.5f,  0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position(-0.5f,  0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 0.0f)},

            Vertex{Position(-0.5f, -0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position( 0.5f, -0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position(-0.5f,  0.5f,  0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position(-0.5f, -0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},

            Vertex{Position(-0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position(-0.5f,  0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position(-0.5f, -0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position(-0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},

            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position( 0.5f,  0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position( 0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position( 0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position( 0.5f, -0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},

            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position( 0.5f, -0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position( 0.5f, -0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position( 0.5f, -0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position(-0.5f, -0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position(-0.5f, -0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},

            Vertex{Position(-0.5f,  0.5f, -0.5f), TextureCoord(0.0f, 1.0f)},
            Vertex{Position( 0.5f,  0.5f, -0.5f), TextureCoord(1.0f, 1.0f)},
            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position( 0.5f,  0.5f,  0.5f), TextureCoord(1.0f, 0.0f)},
            Vertex{Position(-0.5f,  0.5f,  0.5f), TextureCoord(0.0f, 0.0f)},
            Vertex{Position(-0.5f,  0.5f, -0.5f), TextureCoord(0.0f, 1.0f)}
        };
    };
}