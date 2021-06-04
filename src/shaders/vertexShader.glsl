#version 430 core
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 offset;
layout (location = 2) in vec3 color;

out vec3 vColor;


uniform mat4 u_projection;
uniform mat4 u_model;

void main() {
    gl_Position = u_projection * u_model * vec4(vertex + offset, 0.0, 1.0);
    vColor = color;
    //    if (int(offset.x) % 2 == 0) {
    //        vColor = vec3(0.0, 0.0, 0.0);
    //    } else {
    //        vColor = vec3(1.0, 1.0, 1.0);
    //    }
}

