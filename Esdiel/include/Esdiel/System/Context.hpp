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
        Context();

        ///
        Context(Context const&) = delete;

        ///
        Context& operator = (Context const&) = delete;

        ///
        Context(Context&&) = delete;

        ///
        Context& operator = (Context&&) = delete;

        ///
        ~Context();

        ///
        bool Initialize();

        ///
        void Shutdown();

    private:

        bool m_initialized;
    };
}
