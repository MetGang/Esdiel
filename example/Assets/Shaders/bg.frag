#version 330 core

// Input from vertex shader
in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoord;

// Output for OpenGL
out vec4 fragColor;

// Defines
#define pi 3.14159265359
#define pi2 1.57079632679
#define pi4 0.78539816339

// Uniforms
uniform sampler2D tex;

uniform float time;

void main()
{
    vec4 pixel = texture2D(tex, v_texCoord) * v_color;

    pixel.rgb = (pixel.rgb - 0.5) * tan((sin(time) * 0.015 + 0.03 + 1.0) * pi4) + 0.5;

    fragColor = pixel;
}
