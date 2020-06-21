#pragma once

// Esdiel
#include <Esdiel/Audio/Sound.hpp>
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/RenderLayer.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Window.hpp>
#include <Esdiel/Game/Entity.hpp>
#include <Esdiel/Game/GameState.hpp>

// C++
#include <memory>
#include <random>

//
union SDL_Event;

namespace esd
{
    ///
    class World
    {
    public:

        ///
        World(Window const& window, SDL_Event const& event);

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
        bool Initialize();

        ///
        void TogglePause();

        ///
        void ProcessEvent();

        ///
        void ProcessLogic();

        ///
        void ProcessCollision();

        ///
        void ProcessAnimation();

        ///
        void Render();

    private:

        ///
        void M_StartGame();

        ///
        void M_StopGame();

        ///
        void M_SpawnPlayer();

        ///
        void M_SpawnBonus();

        ///
        void M_SpawnEnemy();

        ///
        Vec2f M_GetSpawnPosition();

        Window const* m_window;
        SDL_Event const* m_event;

        std::random_device m_randomDevice;
        std::mt19937 m_mt19937;
        std::discrete_distribution<std::underlying_type_t<BonusType>> m_bonusDistribution;
        std::discrete_distribution<std::underlying_type_t<EnemyType>> m_enemyDistribution;
        std::uniform_real_distribution<float> m_piDistribution;
        std::uniform_real_distribution<float> m_posDistribution;

        Clock m_pauseClock;
        Clock m_timeClock;
        Clock m_auxClock;
        GameState m_gameState;
        int32_t m_score;

        RenderLayer m_gameLayer;
        RenderLayer m_guiLayer;
        ShaderProgram m_defaultProgram;
        ShaderProgram m_bgProgram;
        ShaderProgram m_ppProgram;
        ShaderProgram m_guiProgram;
        Camera m_gameCamera;
        Camera m_staticCamera;

        Vec2u m_size;
        Vec4i m_mousePosition;

        Texture m_texMenuBg;
        Sprite m_sprMenuBg;

        Texture m_texMenuLogo;
        Sprite m_sprMenuLogo;

        Texture m_texGameOverBg;
        Sprite m_sprGameOverBg;

        Texture m_texGameOverScore;
        Sprite m_sprGameOverScore;

        Texture m_texBg;
        Sprite m_sprBg;

        Texture m_texExplosion;
        Sprite m_sprExplosion[2];
        Animation m_animExplosion[2];

        Texture m_texCursor;
        Sprite m_sprCursor;
        Animation m_animCursor;

        Entity m_player;
        Texture m_texPlayer;

        Entity m_bonus;
        Texture m_texBonuses[+BonusType::COUNT];

        std::vector<std::unique_ptr<Entity>> m_enemies;
        Texture m_texEnemies[+EnemyType::COUNT];

        Sound m_sndBonusPickups[+BonusType::COUNT];

        Sound m_sndExplosion[2];

        Sound m_sndMenu;

        Sound m_sndAmbient;
        Clock m_ambientLoopClock;

        Sound m_sndGameOver;
    };
}
