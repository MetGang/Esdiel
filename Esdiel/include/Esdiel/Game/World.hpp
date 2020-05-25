#pragma once

// Esdiel
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/RenderLayer.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Window.hpp>
#include <Esdiel/Game/Entity.hpp>
#include <Esdiel/Game/GameState.hpp>

//
union SDL_Event;

namespace esd
{
    ///
    class World
    {
    public:

        ///
        World();

        ///
        World(World const&) = delete;

        ///
        World& operator = (World const&) = delete;

        ///
        World(World&&) = delete;

        ///
        World& operator = (World&&) = delete;

        ///
        ~World() = default;

        ///
        bool Initialize(Window const& window);

        ///
        void TogglePause();

        ///
        void ProcessEvent(Window const& window, SDL_Event const& event);

        ///
        void ProcessLogic(Duration_t const& duration);

        ///
        void ProcessCollision();

        ///
        void ProcessAnimation();

        ///
        void Render(Window const& window);

    private:

        Clock m_clock;
        GameState m_gameState;

        RenderLayer m_gameLayer;
        RenderLayer m_guiLayer;
        ShaderProgram m_defaultProgram;
        ShaderProgram m_ppProgram;
        ShaderProgram m_guiProgram;
        Camera m_gameCamera;
        Camera m_staticCamera;

        Vec4i m_mousePosition;
        
        Texture m_textures[+EntityType::COUNT];

        Entity m_player;
        std::vector<Entity> m_enemies;
        // Bonus m_bonus;
    };
}
