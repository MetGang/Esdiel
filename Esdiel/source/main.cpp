#include <Esdiel/Audio/Sound.hpp>
#include <Esdiel/System/Context.hpp>
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/RenderLayer.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Sprite.hpp>
#include <Esdiel/Graphics/Texture.hpp>
#include <Esdiel/Graphics/Transformable.hpp>
#include <Esdiel/Graphics/VertexBuffer.hpp>
#include <Esdiel/Graphics/Window.hpp>

#include <iostream>

int main()
{
    esd::Context context;

    if (!context.Initialize())
    {
        return -1;
    }

    esd::Window window;

    if (!window.Create({ 1280u, 720u }, "Esdiel"))
    {
        return -2;
    }

    window.SetFramerateLimit(60u);

    esd::Camera camera;

    esd::Shader vert;
    std::cout << vert.LoadFromFile(esd::ShaderType::Vertex, "Assets/Shaders/default.vert");
    esd::Shader frag;
    std::cout << frag.LoadFromFile(esd::ShaderType::Fragment, "Assets/Shaders/default.frag");
    esd::ShaderProgram shaderProgram;
    std::cout << shaderProgram.LinkShaders({ &vert, &frag });

    esd::Texture tex;
    std::cout << tex.LoadFromFile("Assets/Textures/LaraCroft.png");

    esd::Sound snd;
    std::cout << snd.LoadFromFile("Assets/Sounds/file_example_WAV_1MG.wav");

    esd::Sprite spr;
    spr.SetTexture(tex);
    spr.SetTextureRect({ 450, 450, 450, 450 });

    esd::Sprite aspr;
    aspr.SetTexture(tex);
    aspr.SetPosition({ 500, 50, 0 });
    aspr.SetRotation({ 0, 0, 0.5f });
    aspr.SetColor({ 1, 1, 1, 0.5f });
    aspr.SetAnimationFrame(1, 2, { 450, 450 });

    esd::RenderLayer rl;
    std::cout << rl.Create(window.GetSize());

    while (window.IsOpen())
    {
        SDL_Event event;

        while (window.PollEvent(event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
            {
                window.Close();
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_A)
                {
                    snd.Play();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                {
                    snd.Stop();
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                {
                    snd.Toggle();
                }
            }
        }

        // std::cout << esd::AsMilliseconds(window.GetDT()) << '\n';

        rl.Clear();

        spr.Render(rl, shaderProgram, camera);
    
        window.Clear();

        rl.Render(window, shaderProgram, camera);
        aspr.Render(window, shaderProgram, camera);

        window.Display();
    }

    return 0;
}
