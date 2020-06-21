#version 330 core

// Vertex from OpenGL
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

// Output for fragment shader
out vec3 v_position;
out vec4 v_color;
out vec2 v_texCoord;

// Uniforms
uniform mat4x4 mvp;

void main()
{
    gl_Position = vec4(mvp * vec4(position, 1.0));

    v_position = gl_Position.xyz;
    v_color = color;
    v_texCoord = texCoord;
}
