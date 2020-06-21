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

uniform bool isPaused;

uniform struct Vignette
{
    float radius;
    float softness;
    float opacity;

} vignette = Vignette(1.0, 0.6, 1.0);

void main()
{
    vec4 pixel = texture2D(tex, v_texCoord) * v_color;

    float factor = smoothstep(vignette.radius, vignette.radius - vignette.softness, length(v_position.xy));

    pixel.rgb = mix(pixel.rgb, pixel.rgb * factor, vignette.opacity);

    if (isPaused)
    {
        pixel.rgb = vec3(pixel.r * 0.21 + pixel.g * 0.72 + pixel.b * 0.07);
    }

    fragColor = pixel;
}
