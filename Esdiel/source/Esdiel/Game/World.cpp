#include <Esdiel/Game/World.hpp>

// C++
#include <algorithm>
#include <future>

// SDL2
#include <SDL2/SDL_events.h>

#include <iostream>

namespace esd
{
    World::World()
        : m_clock {}
        , m_gameState { GameState::Menu }
        , m_gameLayer {}
        , m_guiLayer {}
        , m_defaultProgram {}
        , m_ppProgram {}
        , m_guiProgram {}
        , m_gameCamera {}
        , m_staticCamera {}
        , m_mousePosition {}
        , m_textures {}
        , m_player {}
        , m_enemies {}
    {
        m_enemies.reserve(100u);
    }

    bool World::Initialize(Window const& window)
    {
        if (m_gameLayer.Create(window.GetSize()) && m_guiLayer.Create(window.GetSize()))
        {
            if (
                m_defaultProgram.LoadFromFile("Assets/Shaders/default.vert", "Assets/Shaders/default.frag") &&
                m_ppProgram.LoadFromFile("Assets/Shaders/default.vert", "Assets/Shaders/default.frag") &&
                m_guiProgram.LoadFromFile("Assets/Shaders/default.vert", "Assets/Shaders/default.frag")
            )
            {
                if (
                    m_textures[+EntityType::Player].LoadFromFile("Assets/Textures/player.png") &&
                    m_textures[+EntityType::Static].LoadFromFile("Assets/Textures/static.png") &&
                    m_textures[+EntityType::Follower].LoadFromFile("Assets/Textures/follower.png") &&
                    m_textures[+EntityType::Stealth].LoadFromFile("Assets/Textures/stealth.png")
                )
                {
                    // m_enemies.emplace_back().Initialize(EntityType::Static, window, m_textures[+EntityType::Static]);
                    // m_enemies.emplace_back().Initialize(EntityType::Follower, window, m_textures[+EntityType::Follower]);
                    m_enemies.emplace_back().Initialize(EntityType::Stealth, window, m_textures[+EntityType::Stealth]);

                    return m_player.Initialize(EntityType::Player, window, m_textures[+EntityType::Player]);
                }
            }
        }
        
        return false;
    }

    void World::TogglePause()
    {
        m_clock.Toggle();

        m_player.TogglePause();

        for (auto& e : m_enemies)
        {
            e.TogglePause();
        }
    }

    void World::ProcessEvent(Window const& window, SDL_Event const& event)
    {
        if (m_clock.IsRunning())
        {
            if (event.type == SDL_MOUSEMOTION)
            {
                m_mousePosition = { event.motion.x, window.GetSize().y - event.motion.y, event.motion.xrel, -event.motion.yrel };
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_P && event.key.repeat == 0)
            {
                TogglePause();
            }

            m_player.ProcessEvent(event);
        }
    }

    void World::ProcessLogic(Duration_t const& duration)
    {
        if (m_clock.IsRunning())
        {
            auto const dt = AsMilliseconds(duration);

            m_player.ProcessLogic(dt, m_mousePosition, m_player);

            for (auto& e : m_enemies)
            {
                e.ProcessLogic(dt, m_mousePosition, m_player);
            }
        }
    }

    void World::ProcessCollision()
    {
        if (m_clock.IsRunning())
        {
            m_player.ProcessCollision();
        }
    }

    void World::ProcessAnimation()
    {
        if (m_clock.IsRunning())
        {
            m_player.ProcessAnimation();

            for (auto& e : m_enemies)
            {
                e.ProcessAnimation();
            }
        }
    }

    void World::Render(Window const& window)
    {
        if (m_clock.IsRunning())
        {
            // m_gameCamera.SetPosition({
            //     std::clamp(m_player.GetPosition().x - window.GetSizeHalved().x, -100.0f, 100.0f),
            //     std::clamp(m_player.GetPosition().y - window.GetSizeHalved().y, -100.0f, 100.0f),
            //     0.0f
            // });
        }

        //

        m_gameLayer.Clear();

        m_player.Render(m_gameLayer, m_defaultProgram, m_gameCamera);

        for (auto const& e : m_enemies)
        {
            e.Render(m_gameLayer, m_defaultProgram, m_gameCamera);
        }

        m_gameLayer.Render(window, m_ppProgram, m_staticCamera);

        //

        m_guiLayer.Clear();

        m_guiLayer.Render(window, m_guiProgram, m_staticCamera);
    }
}
