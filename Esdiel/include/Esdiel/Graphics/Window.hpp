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
        ~Window();

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        GraphicsContext_t GetGraphicsContext() const;

        ///
        bool Create(Vec2u const& size, char const* name);

        ///
        void Show();

        ///
        void Hide();

        ///
        void Close();

        ///
        bool PollEvent(SDL_Event& event);

        ///
        void SetFramerateLimit(uint32_t limit);

        ///
        Duration_t GetDT() const;

        ///
        Vec2u const& GetSize() const;

        ///
        bool IsOpen() const;

        ///
        bool IsValid() const;

        ///
        void Bind() const;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 1.0f }) const;

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
        void M_Defaultize();

        ///
        void M_Destroy();

        NativeHandle_t m_window;
        GraphicsContext_t m_graphicsContext;
        Vec2u m_size;
        Duration_t m_framerateLimit;
        Clock m_dtClock;
        bool m_isOpen;
    };
}
