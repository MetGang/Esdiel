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

    SDL_Event event;

    //

    auto world = esd::World{ window, event };

    if (!world.Initialize())
    {
        return -3;
    }

    //

    while (window.IsOpen())
    {
        event = SDL_Event{};
        
        while (window.PollEvent(event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
            {
                window.Close();
            }

            world.ProcessEvent();
        }

        //

        world.ProcessLogic();

        //

        world.ProcessCollision();

        //

        world.ProcessAnimation();

        //
    
        window.Clear();

        world.Render();

        window.Display();
    }

    return 0;
}
