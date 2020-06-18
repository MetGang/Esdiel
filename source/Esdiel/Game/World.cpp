#include <Esdiel/Game/World.hpp>

// Esdiel
#include <Esdiel/Math/Functions.hpp>

// C++
#include <algorithm>
#include <future>

// SDL2
#include <SDL2/SDL_events.h>

#include <iostream>

namespace esd
{
    World::World(Window const& window, SDL_Event const& event)
        : m_window { &window }
        , m_event { &event }
        , m_randomDevice {}
        , m_mt19937 { m_randomDevice() }
        , m_bonusDistribution {
            7.0, // Regular
            1.5, // Good
            2.0, // Killer
        }
        , m_enemyDistribution {
            1.8, // Static
            3.6, // Follower
            2.0, // Stealth
            2.0, // Fatty
            1.5, // Mouser
            1.5, // Madman
            0.8, // Eater
            1.4, // Guardian
            2.0, // Retard
            4.0, // Rotador
        }
        , m_piDistribution { -pi, pi }
        , m_posDistribution { 0.0, 1.0f }
        , m_pauseClock {}
        , m_timeClock {}
        , m_gameState { GameState::Menu }
        , m_score { 0 }
        , m_gameLayer {}
        , m_guiLayer {}
        , m_defaultProgram {}
        , m_ppProgram {}
        , m_guiProgram {}
        , m_gameCamera {}
        , m_staticCamera {}
        , m_mousePosition {}
        , m_player {}
        , m_texPlayer {}
        , m_bonus {}
        , m_texBonuses {}
        , m_enemies {}
        , m_texEnemies {}
    {
        // m_enemies.reserve(100u);
    }

    bool World::Initialize()
    {
        if (m_gameLayer.Create(m_window->GetSize()) && m_guiLayer.Create(m_window->GetSize()))
        {
            if (
                m_defaultProgram.LoadFromFile("Assets/Shaders/default.vert", "Assets/Shaders/default.frag") &&
                m_ppProgram.LoadFromFile("Assets/Shaders/pp.vert", "Assets/Shaders/pp.frag") &&
                m_guiProgram.LoadFromFile("Assets/Shaders/default.vert", "Assets/Shaders/default.frag")
            )
            {
                if (
                    m_texCursor.LoadFromFile("Assets/Textures/cursor.png") &&

                    m_texMenuBg.LoadFromFile("Assets/Textures/menu_bg.png") &&
                    m_texMenuLogo.LoadFromFile("Assets/Textures/menu_logo.png") &&
                    m_texMenuText.LoadFromFile("Assets/Textures/menu_text.png") &&

                    m_texBg.LoadFromFile("Assets/Textures/background.png") &&

                    m_texPlayer.LoadFromFile("Assets/Textures/player.png") &&

                    m_texBonuses[+BonusType::Regular].LoadFromFile("Assets/Textures/Bonuses/regular.png") &&
                    m_texBonuses[+BonusType::Good].LoadFromFile("Assets/Textures/Bonuses/good.png") &&
                    m_texBonuses[+BonusType::Killer].LoadFromFile("Assets/Textures/Bonuses/killer.png") &&

                    m_texEnemies[+EnemyType::Static].LoadFromFile("Assets/Textures/Enemies/static.png") &&
                    m_texEnemies[+EnemyType::Follower].LoadFromFile("Assets/Textures/Enemies/follower.png") &&
                    m_texEnemies[+EnemyType::Stealth].LoadFromFile("Assets/Textures/Enemies/stealth.png") &&
                    m_texEnemies[+EnemyType::Fatty].LoadFromFile("Assets/Textures/Enemies/fatty.png") &&
                    m_texEnemies[+EnemyType::Mouser].LoadFromFile("Assets/Textures/Enemies/mouser.png") &&
                    m_texEnemies[+EnemyType::Madman].LoadFromFile("Assets/Textures/Enemies/madman.png") &&
                    m_texEnemies[+EnemyType::Eater].LoadFromFile("Assets/Textures/Enemies/eater.png") &&
                    m_texEnemies[+EnemyType::Guardian].LoadFromFile("Assets/Textures/Enemies/guardian.png") &&
                    m_texEnemies[+EnemyType::Retard].LoadFromFile("Assets/Textures/Enemies/static.png") &&
                    m_texEnemies[+EnemyType::Rotador].LoadFromFile("Assets/Textures/Enemies/rotador.png") &&

                    m_sndBonusPickups[+BonusType::Regular].LoadFromFile("Assets/Sounds/Bonuses/regular.wav") &&
                    m_sndBonusPickups[+BonusType::Good].LoadFromFile("Assets/Sounds/Bonuses/good.wav") &&
                    m_sndBonusPickups[+BonusType::Killer].LoadFromFile("Assets/Sounds/Bonuses/good.wav") &&

                    m_sndMenu.LoadFromFile("Assets/Sounds/menu.wav") &&
                    m_sndAmbient.LoadFromFile("Assets/Sounds/ambient.wav") &&
                    m_sndGameOver.LoadFromFile("Assets/Sounds/game_over.wav")
                )
                {
                    m_sprCursor.SetTexture(m_texCursor);
                    m_sprCursor.SetOrigin({ 16.0f, 16.0f, 0.0f });
                    m_animCursor.SetAnimations({ 2 });
                    m_animCursor.SetFrameDuration(std::chrono::milliseconds{ 500 });
                    m_animCursor.SetFrameSize({ 32, 32 });
                    m_animCursor.Play(0);

                    m_sprMenuBg.SetTexture(m_texMenuBg);
                    m_sprMenuBg.SetPosition({ m_window->GetSizeHalved().x, m_window->GetSizeHalved().y, 0.0f });
                    m_sprMenuBg.SetOrigin({ m_texMenuBg.GetSizeHalved().x, m_texMenuBg.GetSizeHalved().y, 0.0f });

                    m_sprMenuLogo.SetTexture(m_texMenuLogo);
                    m_sprMenuLogo.SetPosition({ m_window->GetSizeHalved().x, m_window->GetSize().y * 0.75f, 0.0f });
                    m_sprMenuLogo.SetOrigin({ m_texMenuLogo.GetSizeHalved().x, m_texMenuLogo.GetSizeHalved().y, 0.0f });

                    m_sprMenuText.SetTexture(m_texMenuText);
                    m_sprMenuText.SetPosition({ m_window->GetSizeHalved().x, m_window->GetSize().y * 0.2f, 0.0f });
                    m_sprMenuText.SetOrigin({ m_texMenuText.GetSizeHalved().x, m_texMenuText.GetSizeHalved().y, 0.0f });

                    m_texBg.SetRepeated(true);
                    m_sprBg.SetTexture(m_texBg);
                    m_sprBg.SetTextureRect({ 0.0f, 0.0f, m_window->GetSize().x + 200.0f, m_window->GetSize().y + 200.0f });
                    m_sprBg.SetPosition({ -100.0f, -100.0f, 0.0f });

                    m_sndMenu.Play();

                    return true;
                }
            }
        }
        
        return false;
    }

    void World::TogglePause()
    {
        m_pauseClock.Toggle();
        m_timeClock.Toggle();

        m_player.TogglePause();

        m_bonus.TogglePause();

        for (auto& e : m_enemies)
        {
            e->TogglePause();
        }

        for (auto& s : m_sndBonusPickups)
        {
            s.Toggle();
        }

        m_sndAmbient.Toggle();
        m_ambientLoopClock.Toggle();
    }

    void World::ProcessEvent()
    {
        if (m_event->type == SDL_MOUSEMOTION)
        {
            m_mousePosition = {
                m_event->motion.x + m_gameCamera.GetPosition().x,
                m_window->GetSize().y - m_event->motion.y + m_gameCamera.GetPosition().y,
                m_event->motion.xrel, 
                -m_event->motion.yrel
            };
        }

        if (m_gameState == GameState::Menu)
        {
            if (m_event->type == SDL_KEYDOWN && m_event->key.keysym.scancode == SDL_SCANCODE_RETURN && m_event->key.repeat == 0)
            {
                M_StartGame();
            }
        }
        else if (m_gameState == GameState::InGame)
        {
            if (m_event->type == SDL_KEYDOWN && m_event->key.keysym.scancode == SDL_SCANCODE_P && m_event->key.repeat == 0)
            {
                TogglePause();
            }
        }
    }

    void World::ProcessLogic()
    {
        if (m_gameState == GameState::InGame)
        {
            if (m_ambientLoopClock.CheckStep(std::chrono::seconds{ 60 + 54 }))
            {
                m_sndAmbient.Play();
            }

            if (m_pauseClock.IsRunning())
            {
                auto const dt = AsMilliseconds(m_window->GetDT());
                auto const piRand = m_piDistribution(m_mt19937);

                m_player.ProcessLogic(dt, m_mousePosition, m_player, m_bonus, piRand);

                m_bonus.ProcessLogic(dt, m_mousePosition, m_player, m_bonus, piRand);

                for (auto& e : m_enemies)
                {
                    e->ProcessLogic(dt, m_mousePosition, m_player, m_bonus, piRand);
                }
            }
        }
    }

    void World::ProcessCollision()
    {
        if (m_gameState == GameState::InGame)
        {
            if (m_pauseClock.IsRunning())
            {
                m_player.PrepareCollider();
                
                m_bonus.PrepareCollider();
                
                for (auto& e : m_enemies)
                {
                    e->PrepareCollider();
                }

                //

                if (m_player.ProcessCollision(m_bonus))
                {
                    m_sndBonusPickups[+m_bonus.GetSubType().b].Play();

                    m_score += m_bonus.GetRewardAmount();
                    m_bonus.Kill();

                    M_SpawnEnemy();
                    M_SpawnBonus();
                }
                
                for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
                {
                    if (m_bonus.ProcessCollision(**it))
                    {
                        m_sndBonusPickups[+m_bonus.GetSubType().b].Play();

                        m_score -= m_bonus.GetRewardAmount();
                        m_bonus.Kill();

                        if (m_bonus.GetSubType().b == BonusType::Killer)
                        {
                            (*it)->Kill();
                        }
                        else
                        {
                            M_SpawnEnemy();
                        }

                        M_SpawnBonus();

                        break;
                    }
                }
                
                for (auto it = m_enemies.begin(); it != m_enemies.end(); ++it)
                {
                    if (m_player.ProcessCollision(**it))
                    {
                        m_player.Kill();
                        (*it)->Kill();

                        break;
                    }
                }

                m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(), [](auto const& enemy) { return !enemy->IsAlive(); }), m_enemies.end());

                if (!m_player.IsAlive())
                {
                    M_StopGame();
                }
            }
        }
    }

    void World::ProcessAnimation()
    {
        if (m_gameState == GameState::InGame)
        {
            if (m_pauseClock.IsRunning())
            {
                m_player.ProcessAnimation();

                m_bonus.ProcessAnimation();

                for (auto& e : m_enemies)
                {
                    e->ProcessAnimation();
                }
            }
        }
    }

    void World::Render()
    {
        switch (m_gameState)
        {
            case GameState::Menu:
            {
                m_guiLayer.Clear();

                m_sprMenuBg.Render(*m_window, m_guiProgram, m_staticCamera);

                m_sprMenuLogo.Render(*m_window, m_guiProgram, m_staticCamera);

                m_sprMenuText.Render(*m_window, m_guiProgram, m_staticCamera);

                m_guiLayer.Render(*m_window, m_guiProgram, m_staticCamera);
            }
            break;

            case GameState::InGame:
            {
                if (m_pauseClock.IsRunning())
                {
                    m_gameCamera.SetPosition({
                        std::clamp(m_player.GetPosition().x - m_window->GetSizeHalved().x, -100.0f, 100.0f),
                        std::clamp(m_player.GetPosition().y - m_window->GetSizeHalved().y, -100.0f, 100.0f),
                        0.0f
                    });
                }

                //

                m_gameLayer.Clear();

                m_sprBg.Render(m_gameLayer, m_defaultProgram, m_gameCamera);

                m_player.Render(m_gameLayer, m_defaultProgram, m_gameCamera);

                m_bonus.Render(m_gameLayer, m_defaultProgram, m_gameCamera);

                for (auto const& e : m_enemies)
                {
                    e->Render(m_gameLayer, m_defaultProgram, m_gameCamera);
                }

                m_gameLayer.Render(*m_window, m_ppProgram, m_staticCamera);

                //

                m_guiLayer.Clear();
                
                int mx;
                int my;
                SDL_GetMouseState(&mx, &my);

                m_sprCursor.SetPosition({ mx, m_window->GetSize().y - my, 0.0f });
                m_sprCursor.SetTextureRect(m_animCursor.GetTextureRect());
                m_sprCursor.Render(m_guiLayer, m_guiProgram, m_staticCamera);

                m_guiLayer.Render(*m_window, m_guiProgram, m_staticCamera);
            }
            break;
            
            case GameState::GameOver:
            {
                m_guiLayer.Clear({ 0.0f, 0.0f, 0.1f, 1.0f });

                m_guiLayer.Render(*m_window, m_guiProgram, m_staticCamera);
            }
            break;
        }
    }

    void World::M_StartGame()
    {
        m_sndMenu.Stop();
        m_sndGameOver.Stop();

        m_gameState = GameState::InGame;

        M_SpawnPlayer();
        M_SpawnBonus();
        M_SpawnEnemy();

        m_sndAmbient.Play();
        m_ambientLoopClock.Restart();
    }

    void World::M_StopGame()
    {
        m_gameState = GameState::GameOver;

        m_sndAmbient.Stop();

        m_sndGameOver.Play();

        m_enemies.clear();
    }

    void World::M_SpawnPlayer()
    {
        m_player.Initialize(m_texPlayer, M_GetSpawnPosition());
    }

    void World::M_SpawnBonus()
    {
        auto type = static_cast<BonusType>(m_bonusDistribution(m_mt19937));

        m_bonus.Initialize(type, m_texBonuses[+type], M_GetSpawnPosition());
    }

    void World::M_SpawnEnemy()
    {
        auto type = static_cast<EnemyType>(m_enemyDistribution(m_mt19937));

        m_enemies.emplace_back(std::make_unique<Entity>())->Initialize(type, m_texEnemies[+type], M_GetSpawnPosition());
    }

    Vec2f World::M_GetSpawnPosition()
    {
        return {
            m_posDistribution(m_mt19937) * m_window->GetSize().x,
            m_posDistribution(m_mt19937) * m_window->GetSize().y,
        };
    }
}
