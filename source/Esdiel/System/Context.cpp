#include <Esdiel/System/Context.hpp>

// SDL2
#include <SDL2/SDL.h>

namespace esd
{
    Context::Context()
        : m_initialized { false }
    {

    }

    Context::~Context()
    {
        Shutdown();
    }

    bool Context::Initialize()
    {
        m_initialized = SDL_Init(SDL_INIT_EVERYTHING) == 0;

        return m_initialized;
    }

    void Context::Shutdown()
    {
        if (m_initialized)
        {
            SDL_Quit();

            m_initialized = false;
        }
    }
}
