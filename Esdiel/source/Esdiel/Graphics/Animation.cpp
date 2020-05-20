#include <Esdiel/Graphics/Animation.hpp>

namespace esd
{
    Animation::Animation()
        : m_clock {}
        , m_frameDuration { std::chrono::seconds{ 1 } }
        , m_framesCounts { 1u, 1 }
        , m_frameSize { 1, 1 }
        , m_currentFrame { 0 }
        , m_currentAnimation { 0 }
        , m_fallbackAnimation { 0 }
        , m_isPlayingOnce { false }
    {

    }

    void Animation::SetAnimations(std::initializer_list<uint32_t> il)
    {
        m_framesCounts = il;
    }

    void Animation::SetFrameDuration(Duration_t const& duration)
    {
        m_frameDuration = duration;
    }

    void Animation::SetFrameSize(Vec2u const& frameSize)
    {
        m_frameSize = frameSize;
    }

    Vec4f Animation::GetTextureRect()
    {
        size_t framesAdvanced = m_clock.CheckContinuousStep(m_frameDuration);

        if (m_isPlayingOnce && (m_currentFrame + framesAdvanced) >= m_framesCounts[m_currentAnimation])
        {
            m_isPlayingOnce = false;
            m_currentAnimation = m_fallbackAnimation;
        }
        
        m_currentFrame = (m_currentFrame + framesAdvanced) % m_framesCounts[m_currentAnimation];

        return {
            (m_currentFrame % m_framesCounts[m_currentAnimation]) * m_frameSize.x,
            m_currentAnimation * m_frameSize.y,
            m_frameSize.x,
            m_frameSize.y
        };
    }

    void Animation::Play(uint32_t index)
    {
        m_currentFrame = 0;
        m_currentAnimation = index;
        m_clock.Restart();
    }

    void Animation::PlayOnce(uint32_t index, uint32_t fallbackAnimation)
    {
        Play(index);

        m_isPlayingOnce = true;
        m_fallbackAnimation = fallbackAnimation;
    }

    void Animation::Pause()
    {
        m_clock.Pause();
    }

    void Animation::Unpause()
    {
        m_clock.Start();
    }

    void Animation::Toggle()
    {
        if (IsPlaying())
        {
            Pause();
        }
        else if (IsPaused())
        {
            Unpause();
        }
    }

    bool Animation::IsPlaying() const
    {
        return m_clock.IsRunning();
    }

    bool Animation::IsPaused() const
    {
        return m_clock.IsPaused();
    }
}
