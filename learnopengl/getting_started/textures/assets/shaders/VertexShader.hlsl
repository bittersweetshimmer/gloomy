#version 330 core
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texcoord;

out vec3 f_color;
out vec2 f_texcoord;

void main() {
    gl_Position = vec4(v_position, 1.0);

    f_color = v_color;
    f_texcoord = v_texcoord;
}