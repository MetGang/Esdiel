#include <Esdiel/Game/Entity.hpp>

// Esdiel
#include <Esdiel/Graphics/Window.hpp>
#include <Esdiel/Math/Functions.hpp>

// C++
#include <algorithm>

#include <iostream>

namespace esd
{
    Entity::Entity()
        : m_sprite {}
        , m_animation {}
        , m_animationState { AnimationState::Basic }
        , m_type { static_cast<EntityType>(-1) }
        , m_logicFunction { nullptr }
        , m_collider {}
        , m_position { 0.0f, 0.0f, 0.0f }
        , m_speed { 0.0f }
        , m_rotation { 0.0f }
        , m_opacity { 1.0f }
        , m_isAccelerating { false }
        , m_isAlive { true }
    {
        
    }

    void Entity::SetPosition(Vec3f const& position)
    {
        m_position = position;
    }

    Vec3f const& Entity::GetPosition() const
    {
        return m_position;
    }

    bool Entity::Initialize(EntityType type, Window const& window, Texture const& texture)
    {
        m_sprite.SetTexture(texture);
        m_sprite.SetOrigin({ 32.0f, 32.0f, 0.0f });

        m_animation.SetFrameDuration(std::chrono::milliseconds{ 100 });
        m_animation.SetFrameSize({ 64u, 64u });

        switch (type)
        {
            case EntityType::Player:
            {
                m_type = EntityType::Player;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const& m, Entity const&)
                {
                    auto const distance = Distance(m.x, m.y, e.m_position.x, e.m_position.y);

                    if (distance > 8.0f)
                    {
                        auto const angle = std::atan2(m.y - e.m_position.y, m.x - e.m_position.x);
                        auto const speed = Lerp(e.m_speed, e.m_speed * (e.m_isAccelerating ? 2.3f : 1.7f), std::clamp(distance / 600.0f, 0.0f, 1.0f));

                        e.m_position.x += std::cos(angle) * speed * dt;
                        e.m_position.y += std::sin(angle) * speed * dt;
                        e.m_rotation = angle;
                    }
                };

                m_animation.SetAnimations({
                    4, // Basic
                    4, // Acceleration
                });

                m_collider.SetRadius(18.0f);

                m_position.x = window.GetSizeHalved().x;
                m_position.y = window.GetSizeHalved().y;
                m_speed = 0.4f;
            }
            break;

            case EntityType::Static:
            {
                m_type = EntityType::Static;

                m_logicFunction = +[](Entity& e, int64_t, Vec4i const&, Entity const&)
                {
                    e.m_rotation += 0.01f;              
                };

                m_animation.SetAnimations({
                    6, // Basic
                });

                m_collider.SetRadius(30.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
            }
            break;

            case EntityType::Follower:
            {
                m_type = EntityType::Follower;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p)
                {
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);

                    e.m_position.x += std::cos(angle) * e.m_speed * dt;
                    e.m_position.y += std::sin(angle) * e.m_speed * dt;
                    e.m_rotation = angle;
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_collider.SetRadius(18.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
                m_speed = 0.3f;
            }
            break;

            case EntityType::Stealth:
            {
                m_type = EntityType::Stealth;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p)
                {
                    auto const distance = Distance(p.m_position.x, p.m_position.y, e.m_position.x, e.m_position.y);
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);

                    e.m_position.x += std::cos(angle) * e.m_speed * dt;
                    e.m_position.y += std::sin(angle) * e.m_speed * dt;
                    e.m_rotation = angle;
                    e.m_opacity = Lerp(0.8f, 0.0f, std::clamp(distance / 500.0f, 0.0f, 1.0f));
                };

                m_animation.SetAnimations({
                    2, // Basic
                });

                m_collider.SetRadius(15.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
                m_speed = 0.25f;
            }
            break;

            case EntityType::Fatty:
            {
                m_type = EntityType::Fatty;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p)
                {
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);

                    e.m_position.x += std::cos(angle) * e.m_speed * dt;
                    e.m_position.y += std::sin(angle) * e.m_speed * dt;
                    e.m_rotation = angle;
                };

                m_animation.SetAnimations({
                    2, // Basic
                });

                m_collider.SetRadius(26.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
                m_speed = 0.08f;
            }
            break;

            case EntityType::Mouser:
            {
                m_type = EntityType::Mouser;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const& m, Entity const&)
                {
                    auto const distance = Distance(m.x, m.y, e.m_position.x, e.m_position.y);

                    if (distance > 8.0f)
                    {
                        auto const angle = std::atan2(m.y - e.m_position.y, m.x - e.m_position.x);
                        auto const speed = Lerp(e.m_speed, e.m_speed * 2.0f, std::clamp(distance / 600.0f, 0.0f, 1.0f));

                        e.m_position.x += std::cos(angle) * speed * dt;
                        e.m_position.y += std::sin(angle) * speed * dt;
                        e.m_rotation = angle;
                    }
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_collider.SetRadius(26.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
                m_speed = 0.2f;
            }
            break;

            case EntityType::Madman:
            {
                m_type = EntityType::Madman;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p)
                {
                    auto const distance = Distance(p.m_position.x, p.m_position.y, e.m_position.x, e.m_position.y);
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);
                    auto speed = e.m_speed;

                    if (distance < 220.0f)
                    {
                        speed *= 1.8f;
                        e.m_isAccelerating = true;
                    }
                    else
                    {
                        e.m_isAccelerating = false;
                    }                    

                    e.m_position.x += std::cos(angle) * speed * dt;
                    e.m_position.y += std::sin(angle) * speed * dt;
                    e.m_rotation = angle;
                };

                m_animation.SetAnimations({
                    2, // Basic
                });

                m_collider.SetRadius(15.0f);

                m_position.x = std::rand() % static_cast<int32_t>(window.GetSize().x);
                m_position.y = std::rand() % static_cast<int32_t>(window.GetSize().y);
                m_speed = 0.3f;
            }
            break;

            case EntityType::COUNT: default: break;
        }

        m_animation.Play(+m_animationState);

        return true;
    }

    void Entity::TogglePause()
    {
        m_animation.Toggle();
    }

    void Entity::ProcessEvent(SDL_Event const& event)
    {
        if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_A && event.key.repeat == 0)
        {
            m_isAccelerating = true;
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.scancode == SDL_SCANCODE_A && event.key.repeat == 0)
        {
            m_isAccelerating = false;
        }
    }

    void Entity::ProcessLogic(int64_t dt, Vec4i const& mousePosition, Entity const& player)
    {
        if (m_logicFunction != nullptr)
        {
            m_logicFunction(*this, dt, mousePosition, player);
        }
    }

    void Entity::ProcessCollision()
    {

    }

    void Entity::ProcessAnimation()
    {
        if (m_isAccelerating)
        {
            if (m_animationState != AnimationState::Acceleration)
            {
                m_animationState = AnimationState::Acceleration;
                m_animation.Play(+m_animationState);
            }
        }
        else
        {
            if (m_animationState != AnimationState::Basic)
            {
                m_animationState = AnimationState::Basic;
                m_animation.Play(+m_animationState);
            }
        }

        m_sprite.SetPosition(m_position);
        m_sprite.SetRotation({ 0.0f, 0.0f, m_rotation });
        m_sprite.SetColor({ 1.0f, 1.0f, 1.0f, m_opacity });
        m_sprite.SetTextureRect(m_animation.GetTextureRect());
    }

    void Entity::Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        m_sprite.Render(renderLayer, shaderProgram, camera);
    }
}
