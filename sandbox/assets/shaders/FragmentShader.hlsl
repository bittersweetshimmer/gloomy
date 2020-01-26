#version 330 core
out vec4 o_color;

in vec2 f_texcoord;
in vec3 f_color;

uniform sampler2D u_texture;

void main() {
    o_color = texture(u_texture, f_texcoord) * vec4(f_color, 1.0);
}