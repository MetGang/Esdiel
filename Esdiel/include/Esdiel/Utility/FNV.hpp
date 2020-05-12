#pragma once

// Esdiel
#include <Esdiel/Core.hpp>

namespace esd
{
    using Hash8_t  = uint8_t;
    using Hash16_t = uint16_t;
    using Hash32_t = uint32_t;
    using Hash64_t = uint64_t;

    /// Computes 32-bit Fowler–Noll–Vo hash from given null-terminated source
    template <typename InputIt>
    constexpr Hash32_t FNV1_32(InputIt begin)
    {
        Hash32_t value = 0x811C9DC5u;

        while (*begin)
        {
            value *= 0x1000193u;
            value ^= *begin;
            ++begin;
        }

        return value;
    }

    /// Computes 32-bit Fowler–Noll–Vo hash from given range
    template <typename InputIt>
    constexpr Hash32_t FNV1_32(InputIt begin, InputIt end)
    {
        Hash32_t value = 0x811C9DC5u;

        while (begin != end)
        {
            value *= 0x1000193u;
            value ^= *begin;
            ++begin;
        }

        return value;
    }

    /// Computes 64-bit Fowler–Noll–Vo hash from given null-terminated source
    template <typename InputIt>
    constexpr Hash64_t FNV1_64(InputIt begin)
    {
        Hash64_t value = 0xCBF29CE484222325ull;

        while (*begin)
        {
            value *= 0x100000001B3ull;
            value ^= *begin;
            ++begin;
        }

        return value;
    }

    /// Computes 64-bit Fowler–Noll–Vo hash from given range
    template <typename InputIt>
    constexpr Hash64_t FNV1_64(InputIt begin, InputIt end)
    {
        Hash64_t value = 0xCBF29CE484222325ull;

        while (begin != end)
        {
            value *= 0x100000001B3ull;
            value ^= *begin;
            ++begin;
        }

        return value;
    }

    /// Computes 32-bit alternative Fowler–Noll–Vo hash from given null-terminated source
    template <typename InputIt>
    constexpr Hash32_t FNV1a_32(InputIt begin)
    {
        Hash32_t value = 0x811C9DC5u;

        while (*begin)
        {
            value ^= *begin;
            value *= 0x1000193u;
            ++begin;
        }

        return value;
    }

    /// Computes 32-bit alternative Fowler–Noll–Vo hash from given range
    template <typename InputIt>
    constexpr Hash32_t FNV1a_32(InputIt begin, InputIt end)
    {
        Hash32_t value = 0x811C9DC5u;

        while (begin != end)
        {
            value ^= *begin;
            value *= 0x1000193u;
            ++begin;
        }

        return value;
    }

    /// Computes 64-bit alternative Fowler–Noll–Vo hash from given null-terminated source
    template <typename InputIt>
    constexpr Hash64_t FNV1a_64(InputIt begin)
    {
        Hash64_t value = 0xCBF29CE484222325ull;

        while (*begin)
        {
            value ^= *begin;
            value *= 0x100000001B3ull;
            ++begin;
        }

        return value;
    }

    /// Computes 64-bit alternative Fowler–Noll–Vo hash from given range
    template <typename InputIt>
    constexpr Hash64_t FNV1a_64(InputIt begin, InputIt end)
    {
        Hash64_t value = 0xCBF29CE484222325ull;

        while (begin != end)
        {
            value ^= *begin;
            value *= 0x100000001B3ull;
            ++begin;
        }

        return value;
    }
}
