#pragma once

#include <Types/FloatingType.hpp>

class Enthropy
{
public:
    constexpr Enthropy(FloatingType jPrKgPrK) :
        _jPrKgPrK(jPrKgPrK)
    {}

#define Type Enthropy
#define Value _jPrKgPrK
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Enthropy FromJPrKgPrK(FloatingType jPrKgPrK)
    {
        return Enthropy(jPrKgPrK);
    }
    FloatingType GetJPrKgPrK() const
    {
        return _jPrKgPrK;
    }

private:
    FloatingType _jPrKgPrK;
};
