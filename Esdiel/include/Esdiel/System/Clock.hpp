#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

// C++
#include <chrono>

namespace esd
{
    using SteadyClock_t = std::chrono::steady_clock;
    using SystemClock_t = std::chrono::system_clock;
    using Duration_t    = SteadyClock_t::duration;
    using TimePoint_t   = SteadyClock_t::time_point;
    using Period_t      = SteadyClock_t::period;

    ///
    class Clock
    {
    public:

        ///
        static TimePoint_t Now();

        ///
        Clock();

        ///
        Clock(TimePoint_t const& timePoint);

        ///
        Clock(Clock const&) = default;

        ///
        Clock& operator = (Clock const&) = default;

        ///
        Clock(Clock&& rhs);

        ///
        Clock& operator = (Clock&& rhs);

        ///
        ~Clock() = default;

        ///
        Duration_t GetElapsedDuration() const;

        ///
        void Start();

        ///
        void Pause();

        ///
        void Toggle();

        ///
        Duration_t Restart();

        ///
        void Advance(Duration_t const& duration, bool advanceBackwards = false);

        ///
        bool IsRunning() const;

        ///
        bool IsPaused() const;

        ///
        bool HasPassed(Duration_t const& duration) const;

        ///
        bool CheckStep(Duration_t const& duration);

        ///
        bool CheckFixedStep(Duration_t const& duration);

        ///
        size_t CheckContinuousStep(Duration_t const& duration);

    private:

        TimePoint_t m_refPoint;
        TimePoint_t m_pausePoint;
    };

    ///
    template <typename Rep, typename Period>
    constexpr Duration_t AsDefaultDuration(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<Duration_t>(duration);
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsNanoseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsMicroseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsMilliseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsFSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    }

    ///
    template <typename Rep, typename Period>
    constexpr auto AsDSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }

    ///
    char const* GetReadableTime(Duration_t const& duration);
}
