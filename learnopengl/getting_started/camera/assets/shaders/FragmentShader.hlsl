#version 330 core
out vec4 o_color;

in vec2 f_texcoord;

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main() {
    o_color = mix(texture(u_texture1, f_texcoord), texture(u_texture2, f_texcoord), 0.2);
}