#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

// SDL2
#include <SDL2/SDL_audio.h>

namespace esd
{
    ///
    class Sound
    {
    public:

        ///
        Sound() noexcept;

        ///
        Sound(Sound const&) = delete;

        ///
        Sound& operator = (Sound const&) = delete;

        ///
        Sound(Sound&& rhs) noexcept;

        ///
        Sound& operator = (Sound&& rhs) noexcept;

        ///
        ~Sound() noexcept;

        ///
        bool LoadFromFile(char const* filename) noexcept;

        ///
        void Play() const noexcept;

        ///
        void Stop() const noexcept;

        ///
        void Pause() const noexcept;

        ///
        void Unpause() const noexcept;

        ///
        void Toggle() const noexcept;

        ///
        bool IsPlaying() const noexcept;

        ///
        bool IsPaused() const noexcept;

    private:

        ///
        void M_Defaultize() noexcept;

        ///
        void M_Destroy() const noexcept;

        SDL_AudioSpec m_audioSpec;
        uint8_t* m_buffer;
        uint32_t m_bufferLength;
        SDL_AudioDeviceID m_deviceID;
    };
}
