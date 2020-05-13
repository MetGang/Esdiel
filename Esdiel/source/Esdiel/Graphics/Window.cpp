#include <Esdiel/Graphics/Window.hpp>

// Esdiel
#include <Esdiel/Graphics/Camera.hpp>
#include <Esdiel/Graphics/ShaderProgram.hpp>
#include <Esdiel/Graphics/Transform.hpp>

// C++
#include <cstdio>
#include <thread>

// glad
#include <glad/glad.h>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>

namespace esd
{
    Window::Window()
        : m_window { nullptr }
        , m_graphicsContext { nullptr }
        , m_size {}
        , m_framerateLimit {}
        , m_dtClock {}
        , m_isOpen { false }
    {

    }

    Window::~Window()
    {
        M_Destroy();
    }
    
    Window::NativeHandle_t Window::GetNativeHandle() const noexcept
    {
        return m_window;
    }

    Window::GraphicsContext_t Window::GetGraphicsContext() const noexcept
    {
        return m_graphicsContext;
    }

    bool Window::Create(Vec2u const& size, char const* name)
    {
        static bool isGladLoaded = false;

        M_Destroy();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_size = size;
        m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, SDL_WINDOW_OPENGL);

        if (m_window)
        {
            m_graphicsContext = SDL_GL_CreateContext(m_window);

            if (m_graphicsContext)
            {
                gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));

                if (!isGladLoaded)
                {
                    if (gladLoadGL())
                    {
                        isGladLoaded = true;
                    }
                    else
                    {
                        // TODO better logging
                        std::fprintf(stderr, "Failed to initialize GLAD\n");
                    }
                }
            }

            glViewport(0, 0, m_size.x, m_size.y);

            m_framerateLimit = Duration_t::zero();

            m_isOpen = true;

            m_dtClock.Restart();

            return true;
        }

        return false;
    }

    void Window::Show() noexcept
    {
        SDL_ShowWindow(m_window);
    }

    void Window::Hide() noexcept
    {
        SDL_HideWindow(m_window);
    }

    void Window::Close() noexcept
    {
        m_isOpen = false;
    }

    bool Window::PollEvent(SDL_Event& event) noexcept
    {
        return SDL_PollEvent(&event) != 0;
    }

    void Window::SetFramerateLimit(uint32_t limit) noexcept
    {
        if (limit == 0)
        {
            m_framerateLimit = Duration_t::zero();
        }
        else
        {
            m_framerateLimit = AsDefaultDuration(std::chrono::duration<float>{ 1.0f / limit });
        }
    }

    Duration_t Window::GetDT() const
    {
        return m_framerateLimit - m_dtClock.GetElapsedDuration();
    }

    Vec2u Window::GetSize() const noexcept
    {
        return m_size;
    }

    bool Window::IsValid() const noexcept
    {
        return m_window;
    }

    bool Window::IsOpen() const noexcept
    {
        return m_isOpen;
    }

    void Window::Bind() const noexcept
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Window::Clear(Vec4f const& color) const noexcept
    {
        Bind();

        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void Window::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();
        mvp *= transform.GetMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void Window::Display()
    {
        Bind();

        SDL_GL_SwapWindow(m_window);

        M_AdjustFramerate();
    }

    void Window::M_AdjustFramerate()
    {
        if (m_framerateLimit != Duration_t::zero())
        {
            std::this_thread::sleep_for(GetDT());
        }

        m_dtClock.Restart();
    }

    void Window::M_Defaultize() noexcept
    {
        m_window = nullptr;
        m_graphicsContext = nullptr;
        m_size = { 0, 0 };
        m_framerateLimit = Duration_t::zero();
        m_dtClock.Restart();
        m_isOpen = false;
    }

    void Window::M_Destroy() noexcept
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            SDL_GL_DeleteContext(m_graphicsContext);
        }
    }
}
