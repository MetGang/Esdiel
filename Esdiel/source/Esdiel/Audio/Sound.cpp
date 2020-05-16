#include <Esdiel/Audio/Sound.hpp>

// C++
#include <utility>

namespace esd
{
    Sound::Sound() noexcept
        : m_audioSpec {}
        , m_buffer { nullptr }
        , m_bufferLength { 0 }
        , m_deviceID { 0 }
    {

    }

    Sound::Sound(Sound&& rhs) noexcept
        : m_audioSpec { std::move(rhs.m_audioSpec) }
        , m_buffer { rhs.m_buffer }
        , m_bufferLength { rhs.m_bufferLength }
        , m_deviceID { rhs.m_deviceID }
    {
        rhs.M_Defaultize();
    }

    Sound& Sound::operator = (Sound&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_audioSpec = std::move(rhs.m_audioSpec);
            m_buffer = rhs.m_buffer;
            m_bufferLength = rhs.m_bufferLength;
            m_deviceID = rhs.m_deviceID;

            rhs.M_Defaultize();
        }

        return *this;
    }

    Sound::~Sound() noexcept
    {
        M_Destroy();
    }

    bool Sound::LoadFromFile(char const* filename) noexcept
    {
        if (SDL_LoadWAV(filename, &m_audioSpec, &m_buffer, &m_bufferLength) != nullptr)
        {
            m_deviceID = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, 0);

            return m_deviceID > 1;
        }
        else
        {
            return false;
        }
    }

    void Sound::Play() const noexcept
    {
        Stop();

        if (SDL_QueueAudio(m_deviceID, m_buffer, m_bufferLength) == 0)
        {
            SDL_PauseAudioDevice(m_deviceID, 0);
        }
    }

    void Sound::Stop() const noexcept
    {
        SDL_ClearQueuedAudio(m_deviceID);
    }

    void Sound::Pause() const noexcept
    {
        SDL_PauseAudioDevice(m_deviceID, 1);
    }

    void Sound::Unpause() const noexcept
    {
        SDL_PauseAudioDevice(m_deviceID, 0);
    }

    void Sound::Toggle() const noexcept
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

    bool Sound::IsPlaying() const noexcept
    {
        return SDL_GetAudioDeviceStatus(m_deviceID) == SDL_AUDIO_PLAYING;
    }

    bool Sound::IsPaused() const noexcept
    {
        return SDL_GetAudioDeviceStatus(m_deviceID) == SDL_AUDIO_PAUSED;
    }

    void Sound::M_Defaultize() noexcept
    {
        m_audioSpec = {};
        m_buffer = nullptr;
        m_bufferLength = 0;
        m_deviceID = 0;
    }

    void Sound::M_Destroy() const noexcept
    {
        if (m_deviceID > 1)
        {
            SDL_CloseAudioDevice(m_deviceID);
        }

        if (m_buffer)
        {
            SDL_FreeWAV(m_buffer);
        }
    }
}