#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    ///
    template <typename T, typename Class>
    void const* OffsetPtrOf(T Class::* member)
    {
        return &(reinterpret_cast<Class*>(0)->*member);
    }

    ///
    template <typename T, typename Class>
    size_t OffsetOf(T Class::* member)
    {
        return reinterpret_cast<size_t>(OffsetPtrOf(member));
    }
}
