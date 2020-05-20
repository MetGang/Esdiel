#pragma once

// Esdiel
#include <Esdiel/Math/Vector.hpp>
#include <Esdiel/System/Clock.hpp>

// C++
#include <vector>

namespace esd
{
    ///
    class Animation
    {
    public:

        using FramesCounts_t = std::vector<uint32_t>;

        ///
        Animation();

        ///
        Animation(Animation const&) = default;

        ///
        Animation& operator = (Animation const&) = default;

        ///
        Animation(Animation&&) noexcept = default;

        ///
        Animation& operator = (Animation&&) noexcept = default;

        ///
        ~Animation() = default;

        ///
        void SetAnimations(std::initializer_list<uint32_t> il);

        ///
        void SetFrameDuration(Duration_t const& duration);

        ///
        void SetFrameSize(Vec2u const& frameSize);

        ///
        Vec4f GetTextureRect();

        ///
        void Play(uint32_t index);

        ///
        void PlayOnce(uint32_t index, uint32_t fallbackAnimation);

        ///
        void Pause();

        ///
        void Unpause();

        ///
        void Toggle();

        ///
        bool IsPlaying() const;

        ///
        bool IsPaused() const;

    private:

        Clock m_clock;
        Duration_t m_frameDuration;
        FramesCounts_t m_framesCounts;
        Vec2u m_frameSize;
        uint32_t m_currentFrame;
        uint32_t m_currentAnimation;
        uint32_t m_fallbackAnimation;
        bool m_isPlayingOnce;
    };
}
