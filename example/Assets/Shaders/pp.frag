#version 330 core

// Input from vertex shader
in vec3 v_position;
in vec4 v_color;
in vec2 v_texCoord;

// Output for OpenGL
out vec4 fragColor;

// Uniforms
uniform sampler2D tex;

void main()
{
    vec4 pixel = texture2D(tex, v_texCoord) * v_color;

    float factor = smoothstep(1.2, 0.01, length(v_position.xy));

	pixel.rgb = mix(pixel.rgb, pixel.rgb * factor, 0.9);

    fragColor = pixel;
}
