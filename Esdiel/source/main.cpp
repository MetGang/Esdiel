#include <Esdiel/Game/World.hpp>
#include <Esdiel/Graphics/Window.hpp>
#include <Esdiel/Math/Vector.hpp>

#include <iostream>

int main(int, char**)
{
    esd::Context context;

    if (!context.Initialize())
    {
        return -1;
    }

    //

    esd::Window window;

    if (!window.Create("Esdiel Study Game"))
    {
        return -2;
    }

    window.SetFramerateLimit(60u);

    //

    esd::World world;

    if (!world.Initialize(window))
    {
        return -3;
    }

    //

    while (window.IsOpen())
    {
        SDL_Event event;

        while (window.PollEvent(event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
            {
                window.Close();
            }

            world.ProcessEvent(window, event);
        }

        //

        world.ProcessLogic(window.GetDT());

        //

        world.ProcessAnimation();

        //
    
        window.Clear();

        world.Render(window);

        window.Display();
    }

    return 0;
}
