#pragma once

// Esdiel
#include <Esdiel/Graphics/Animation.hpp>
#include <Esdiel/Graphics/Sprite.hpp>
#include <Esdiel/Graphics/Texture.hpp>
#include <Esdiel/Game/AnimationState.hpp>
#include <Esdiel/Game/EntityTypes.hpp>
#include <Esdiel/Game/Collider.hpp>

//
union SDL_Event;

namespace esd
{
    ///
    class Entity
    {
    public:

        using LogicFunction_t = void (*)(Entity& e, int64_t dt, Vec4i const& m, Entity const& p, Entity const& b, float r, Clock& c);

        ///
        Entity();

        ///
        Entity(Entity const&) = delete;

        ///
        Entity& operator = (Entity const&) = delete;

        ///
        Entity(Entity&&) noexcept = default;

        ///
        Entity& operator = (Entity&&) noexcept = default;

        ///
        ~Entity() = default;

        ///
        void SetPosition(Vec2f const& position);

        ///
        Vec2f const& GetPosition() const;

        ///
        void Initialize(Texture const& texture, Vec2f const& position);

        ///
        void Initialize(EnemyType type, Texture const& texture, Vec2f const& position);

        ///
        void Initialize(BonusType type, Texture const& texture, Vec2f const& position);

        ///
        void TogglePause();

        ///
        void ProcessLogic(int64_t dt, Vec4i const& mousePosition, Entity const& player, Entity const& bonus, float piRand);

        ///
        void PrepareCollider();

        ///
        bool ProcessCollision(Entity& other);

        ///
        void ProcessAnimation();

        ///
        EntityType GetType() const;

        ///
        EntitySubType GetSubType() const;

        ///
        int32_t GetRewardAmount() const;

        ///
        void Kill();

        ///
        bool IsAlive() const;

        ///
        void Render(RenderLayer const& renderLayer, ShaderProgram const& shaderProgram, Camera const& camera) const;

    private:

        Sprite m_sprite;
        Animation m_animation;
        AnimationState m_animationState;
        Clock m_clock;

        EntityType m_type;
        EntitySubType m_subType;
        LogicFunction_t m_logicFunction;
        int32_t m_reward;

        Collider m_collider;

        Vec2f m_position;
        float m_speed;
        float m_rotation;
        float m_opacity;

        bool m_isAccelerating;
        bool m_isAlive;

    };
}
