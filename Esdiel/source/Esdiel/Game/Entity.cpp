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
        , m_animationState { AnimationState::Move }
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

        m_animation.SetFrameDuration(std::chrono::milliseconds{ 500 });
        m_animation.SetFrameSize({ 64u, 64u });

        switch (type)
        {
            case EntityType::Player:
            {
                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const& m, Entity const& p) {
                    // Follows mouse cursor
                    auto const distance = Distance(m.x, m.y, p.m_position.x, p.m_position.y);

                    if (distance > 8.0f)
                    {
                        auto const dir = glm::normalize(Vec2f{ m.x - p.m_position.x, m.y - p.m_position.y });
                        auto const speed = Lerp(e.m_speed, e.m_speed * (e.m_isAccelerating ? 2.3f : 1.7f), std::clamp(distance / 600.0f, 0.0f, 1.0f));

                        e.m_position.x += dir.x * speed * dt;
                        e.m_position.y += dir.y * speed * dt;
                        e.m_rotation = std::atan2(dir.y, dir.x);
                    }
                };

                m_animation.SetAnimations({
                    4, // Move
                    3, // Acceleration
                });

                m_collider.SetRadius(18.0f);

                m_position.x = window.GetSizeHalved().x;
                m_position.y = window.GetSizeHalved().y;
                m_speed = 0.4f;
            }
            break;

            case EntityType::Static:
            {
                m_logicFunction = +[](Entity& e, int64_t, Vec4i const&, Entity const&) {
                    // Nothing, just stay still (and rotate)
                    e.m_rotation += 0.01f;                    
                };

                m_animation.SetAnimations({
                    6, // Move
                });

                m_collider.SetRadius(30.0f);

                m_position.x = 100.0f;
                m_position.y = 100.0f;
            }
            break;

            case EntityType::Follower:
            {
                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p) {
                    // Follows player
                    auto const dir = glm::normalize(Vec2f{ p.m_position.x - e.m_position.x, p.m_position.y - e.m_position.y });

                    e.m_position.x += dir.x * e.m_speed * dt;
                    e.m_position.y += dir.y * e.m_speed * dt;
                    e.m_rotation = std::atan2(dir.y, dir.x);
                };

                m_animation.SetAnimations({
                    4, // Move
                });

                m_collider.SetRadius(18.0f);

                m_position.x = 100.0f;
                m_position.y = 100.0f;
                m_speed = 0.3f;
            }
            break;

            case EntityType::Stealth:
            {
                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p) {
                    // Follows player, visibility depends on distance to player
                    auto const distance = Distance(p.m_position.x, p.m_position.y, e.m_position.x, e.m_position.y);
                    auto const dir = glm::normalize(Vec2f{ p.m_position.x - e.m_position.x, p.m_position.y - e.m_position.y });

                    e.m_position.x += dir.x * e.m_speed * dt;
                    e.m_position.y += dir.y * e.m_speed * dt;
                    e.m_rotation = std::atan2(dir.y, dir.x);
                    e.m_opacity = Lerp(0.8f, 0.0f, std::clamp(distance / 680.0f, 0.0f, 1.0f));
                };

                m_animation.SetAnimations({
                    2, // Move
                });

                m_collider.SetRadius(15.0f);

                m_position.x = 100.0f;
                m_position.y = 100.0f;
                m_speed = 0.25f;
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
            if (m_animationState == AnimationState::Move)
            {
                m_animationState = AnimationState::Acceleration;
                m_animation.Play(+m_animationState);
            }
        }
        else
        {
            if (m_animationState == AnimationState::Acceleration)
            {
                m_animationState = AnimationState::Move;
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
