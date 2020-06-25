#include <Esdiel/System/Clock.hpp>

// C++
#include <ctime>
#include <cstring>

namespace esd
{
    TimePoint_t Clock::Now()
    {
        return SteadyClock_t::now();
    }

    Clock::Clock()
        : m_refPoint { Now() }
        , m_pausePoint { Duration_t::zero() }
    {

    }

    Clock::Clock(TimePoint_t const& timePoint)
        : m_refPoint { timePoint }
        , m_pausePoint { Duration_t::zero() }
    {

    }

    Clock::Clock(Clock&& rhs) noexcept
        : m_refPoint { rhs.m_refPoint }
        , m_pausePoint { rhs.m_pausePoint }
    {
        rhs.Restart();
    }

    Clock& Clock::operator = (Clock&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_refPoint = rhs.m_refPoint;
            m_pausePoint = rhs.m_pausePoint;

            rhs.Restart();
        }

        return *this;
    }

    Duration_t Clock::GetElapsedDuration() const
    {
        return IsPaused() ? m_pausePoint - m_refPoint : Now() - m_refPoint;
    }

    void Clock::Start()
    {
        m_refPoint += Now() - m_pausePoint;

        m_pausePoint = TimePoint_t{ Duration_t::zero() };
    }

    void Clock::Pause()
    {
        m_pausePoint = Now();
    }

    void Clock::Toggle()
    {
        if (IsPaused())
        {
            Start();
        }
        else
        {
            Pause();
        }
    }

    Duration_t Clock::Restart()
    {
        Duration_t const ret = GetElapsedDuration();

        m_pausePoint = TimePoint_t{ Duration_t::zero() };

        m_refPoint = Now();

        return ret;
    }

    void Clock::Advance(Duration_t const& duration, bool advanceBackwards)
    {
        if (advanceBackwards)
        {
            m_refPoint += duration;
        }
        else
        {
            m_refPoint -= duration;
        }
    }

    bool Clock::IsRunning() const
    {
        return m_pausePoint.time_since_epoch() == Duration_t::zero();
    }

    bool Clock::IsPaused() const
    {
        return m_pausePoint.time_since_epoch() != Duration_t::zero();
    }

    bool Clock::HasPassed(Duration_t const& duration) const
    {
        return duration <= GetElapsedDuration();
    }

    bool Clock::CheckStep(Duration_t const& duration)
    {
        if (HasPassed(duration))
        {
            Restart();

            return true;
        }
        else
        {
            return false;
        }
    }

    bool Clock::CheckFixedStep(Duration_t const& duration)
    {
        if (HasPassed(duration))
        {
            Advance(duration, true);

            return true;
        }
        else
        {
            return false;
        }
    }

    size_t Clock::CheckContinuousStep(Duration_t const& duration)
    {
        size_t count = 0;

        while (CheckFixedStep(duration))
        {
            ++count;
        }

        return count;
    }
}
