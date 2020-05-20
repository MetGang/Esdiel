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
        Sound();

        ///
        Sound(Sound const&) = delete;

        ///
        Sound& operator = (Sound const&) = delete;

        ///
        Sound(Sound&& rhs) noexcept;

        ///
        Sound& operator = (Sound&& rhs) noexcept;

        ///
        ~Sound();

        ///
        bool LoadFromFile(char const* filename);

        ///
        void Play() const;

        ///
        void Stop() const;

        ///
        void Pause() const;

        ///
        void Unpause() const;

        ///
        void Toggle() const;

        ///
        bool IsPlaying() const;

        ///
        bool IsPaused() const;

    private:

        ///
        void M_Defaultize();

        ///
        void M_Destroy() const;

        SDL_AudioSpec m_audioSpec;
        uint8_t* m_buffer;
        uint32_t m_bufferLength;
        SDL_AudioDeviceID m_deviceID;
    };
}
