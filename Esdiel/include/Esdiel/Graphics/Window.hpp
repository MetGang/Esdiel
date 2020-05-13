#pragma once

// Esdiel
#include <Esdiel/System/Clock.hpp>
#include <Esdiel/System/Context.hpp>
#include <Esdiel/Math/Vector.hpp>

// SDL2
#include <SDL2/SDL.h>

namespace esd
{
    //
    class Camera;
    class ShaderProgram;
    class Transform;

    ///
    class Window
    {
    public:

        using NativeHandle_t    = SDL_Window*;
        using GraphicsContext_t = SDL_GLContext;

        ///
        Window();

        ///
        Window(Window const&) = delete;

        ///
        Window& operator = (Window const&) = delete;

        ///
        Window(Window&&) = delete;

        ///
        Window& operator = (Window&&) = delete;

        ///
        ~Window() noexcept;

        ///
        NativeHandle_t GetNativeHandle() const noexcept;

        ///
        GraphicsContext_t GetGraphicsContext() const noexcept;

        ///
        bool Create(Vec2u const& size, char const* name);

        ///
        void Show() noexcept;

        ///
        void Hide() noexcept;

        ///
        void Close() noexcept;

        ///
        bool PollEvent(SDL_Event& event) noexcept;

        ///
        void SetFramerateLimit(uint32_t limit) noexcept;

        ///
        Duration_t GetDT() const;

        ///
        Vec2u GetSize() const noexcept;

        ///
        bool IsValid() const noexcept;

        ///
        bool IsOpen() const noexcept;

        ///
        void Bind() const noexcept;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 1.0f }) const noexcept;

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const;

        ///
        void Display();

    private:

        ///
        void M_AdjustFramerate();

        ///
        void M_Defaultize() noexcept;

        ///
        void M_Destroy() noexcept;

        NativeHandle_t m_window;
        GraphicsContext_t m_graphicsContext;
        Vec2u m_size;
        Duration_t m_framerateLimit;
        Clock m_dtClock;
        bool m_isOpen;
    };
}
