#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    class Context
    {
    public:

        ///
        Context() noexcept;

        ///
        Context(Context const&) = delete;

        ///
        Context& operator = (Context const&) = delete;

        ///
        Context(Context&&) = delete;

        ///
        Context& operator = (Context&&) = delete;

        ///
        ~Context() noexcept;

        ///
        bool Initialize() noexcept;

        ///
        void Shutdown() noexcept;

    private:

        bool m_initialized;
    };
}
