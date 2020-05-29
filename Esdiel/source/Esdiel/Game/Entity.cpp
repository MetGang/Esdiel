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
        , m_subType {}
        , m_logicFunction { nullptr }
        , m_reward { 0u }
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

    void Entity::Initialize(Texture const& texture, Vec3f const& position)
    {
        m_sprite.SetTexture(texture);
        m_sprite.SetOrigin({ 32.0f, 32.0f, 0.0f });

        m_animation.SetFrameDuration(std::chrono::milliseconds{ 100 });
        m_animation.SetFrameSize({ 64, 64 });

        m_type = EntityType::Player;

        m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const& m, Entity const&, Entity const&, float)
        {
            auto const distance = Distance(m.x, m.y, e.m_position.x, e.m_position.y);

            if (distance > 600.0f)
            {
                e.m_isAccelerating = true;
            }
            else
            {
                e.m_isAccelerating = false;
            }            
            
            if (distance > 8.0f)
            {
                auto const angle = std::atan2(m.y - e.m_position.y, m.x - e.m_position.x);
                auto const speed = Lerp(e.m_speed, e.m_speed * (e.m_isAccelerating ? 2.1f : 1.6f), std::clamp(distance / 600.0f, 0.0f, 1.0f));

                e.m_position.x += std::cos(angle) * speed * dt;
                e.m_position.y += std::sin(angle) * speed * dt;
                e.m_rotation = angle;
            }
        };

        m_animation.SetAnimations({
            4, // Basic
            4, // Acceleration
        });

        m_collider.SetRadius(20.0f);

        m_position = position;
        m_speed = 0.4f;

        m_animation.Play(+m_animationState);
    }

    void Entity::Initialize(EnemyType type, Texture const& texture, Vec3f const& position)
    {
        m_sprite.SetTexture(texture);
        m_sprite.SetOrigin({ 32.0f, 32.0f, 0.0f });

        m_animation.SetFrameDuration(std::chrono::milliseconds{ 100 });
        m_animation.SetFrameSize({ 64, 64 });

        m_type = EntityType::Enemy;

        switch (type)
        {
            case EnemyType::Static:
            {
                m_subType.e = EnemyType::Static;

                m_logicFunction = +[](Entity& e, int64_t, Vec4i const&, Entity const&, Entity const&, float)
                {
                    e.m_rotation += 0.01f;
                };

                m_animation.SetAnimations({
                    2, // Basic
                });

                m_collider.SetRadius(30.0f);

                m_position = position;
            }
            break;

            case EnemyType::Follower:
            {
                m_subType.e = EnemyType::Follower;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p, Entity const&, float)
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

                m_position = position;
                m_speed = 0.3f;
            }
            break;

            case EnemyType::Stealth:
            {
                m_subType.e = EnemyType::Stealth;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p, Entity const&, float)
                {
                    auto const distance = Distance(p.m_position.x, p.m_position.y, e.m_position.x, e.m_position.y);
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);

                    e.m_position.x += std::cos(angle) * e.m_speed * dt;
                    e.m_position.y += std::sin(angle) * e.m_speed * dt;
                    e.m_rotation = angle;
                    e.m_opacity = Lerp(0.8f, 0.0f, std::clamp(distance / 500.0f, 0.0f, 1.0f));
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_collider.SetRadius(20.0f);

                m_position = position;
                m_speed = 0.25f;
                m_opacity = 0.0f;
            }
            break;

            case EnemyType::Fatty:
            {
                m_subType.e = EnemyType::Fatty;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p, Entity const&, float)
                {
                    auto const angle = std::atan2(p.m_position.y - e.m_position.y, p.m_position.x - e.m_position.x);

                    e.m_position.x += std::cos(angle) * e.m_speed * dt;
                    e.m_position.y += std::sin(angle) * e.m_speed * dt;
                    e.m_rotation = angle;
                };

                m_animation.SetAnimations({
                    2, // Basic
                });

                m_collider.SetRadius(28.0f);

                m_position = position;
                m_speed = 0.08f;
            }
            break;

            case EnemyType::Mouser:
            {
                m_subType.e = EnemyType::Mouser;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const& m, Entity const&, Entity const&, float)
                {
                    auto const distance = Distance(m.x, m.y, e.m_position.x, e.m_position.y);

                    if (distance > 8.0f)
                    {
                        auto const angle = std::atan2(m.y - e.m_position.y, m.x - e.m_position.x);
                        auto const speed = Lerp(e.m_speed, e.m_speed * 1.8f, std::clamp(distance / 600.0f, 0.0f, 1.0f));

                        e.m_position.x += std::cos(angle) * speed * dt;
                        e.m_position.y += std::sin(angle) * speed * dt;
                        e.m_rotation = angle;
                    }
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_collider.SetRadius(16.0f);

                m_position = position;
                m_speed = 0.18f;
            }
            break;

            case EnemyType::Madman:
            {
                m_subType.e = EnemyType::Madman;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const& p, Entity const&, float)
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

                m_collider.SetRadius(18.0f);

                m_position = position;
                m_speed = 0.3f;
            }
            break;

            case EnemyType::Eater:
            {
                m_subType.e = EnemyType::Eater;

                m_logicFunction = +[](Entity& e, int64_t dt, Vec4i const&, Entity const&, Entity const& b, float)
                {
                    auto const distance = Distance(b.m_position.x, b.m_position.y, e.m_position.x, e.m_position.y);
                    auto const angle = std::atan2(b.m_position.y - e.m_position.y, b.m_position.x - e.m_position.x);
                    auto speed = e.m_speed;

                    if (distance < 180.0f)
                    {
                        speed *= 1.2f;
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
                    4, // Basic
                    4, // Acceleration
                });

                m_collider.SetRadius(22.0f);

                m_position = position;
                m_speed = 0.11f;
            }
            break;

            //

            case EnemyType::COUNT: default: break;
        }

        m_animation.Play(+m_animationState);
    }

    void Entity::Initialize(BonusType type, Texture const& texture, Vec3f const& position)
    {
        m_sprite.SetTexture(texture);
        m_sprite.SetOrigin({ 32.0f, 32.0f, 0.0f });

        m_animation.SetFrameDuration(std::chrono::milliseconds{ 100 });
        m_animation.SetFrameSize({ 64, 64 });

        m_type = EntityType::Bonus;

        switch (type)
        {
            case BonusType::Regular:
            {
                m_subType.b = BonusType::Regular;

                m_logicFunction = +[](Entity&, int64_t, Vec4i const&, Entity const&, Entity const&, float)
                {
                    
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_reward = 1;

                m_collider.SetRadius(18.0f);

                m_position = position;
            }
            break;

            case BonusType::Good:
            {
                m_subType.b = BonusType::Good;

                m_logicFunction = +[](Entity&, int64_t, Vec4i const&, Entity const&, Entity const&, float)
                {
                    
                };

                m_animation.SetAnimations({
                    4, // Basic
                });

                m_reward = 5;

                m_collider.SetRadius(18.0f);

                m_position = position;
            }
            break;

            //

            case BonusType::COUNT: default: break;
        }

        m_animation.Play(+m_animationState);

        m_isAlive = true;
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

    void Entity::ProcessLogic(int64_t dt, Vec4i const& mousePosition, Entity const& player, Entity const& bonus, float piRand)
    {
        if (m_logicFunction != nullptr)
        {
            m_logicFunction(*this, dt, mousePosition, player, bonus, piRand);
        }
    }

    void Entity::PrepareCollider()
    {
        m_collider.SetPosition({ m_position.x, m_position.y });
    }

    bool Entity::ProcessCollision(Entity& other)
    {
        return m_isAlive && other.m_isAlive && m_collider.CollidesWith(other.m_collider);
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

    EntityType Entity::GetType() const
    {
        return m_type;
    }

    EntitySubType Entity::GetSubType() const
    {
        return m_subType;
    }

    int32_t Entity::GetRewardAmount() const
    {
        return m_reward;
    }

    void Entity::Kill()
    {
        m_isAlive = false;
    }

    bool Entity::IsAlive() const
    {
        return m_isAlive;
    }

    void Entity::Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        m_sprite.Render(renderLayer, shaderProgram, camera);
    }
}
