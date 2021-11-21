#pragma once

#include <Types/FloatingType.hpp>

class Density
{
public:
    constexpr Density(FloatingType kgM3) :
        _kgM3(kgM3)
    {}

#define Type Density
#define Value _kgM3
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Density FromKgM3(FloatingType kgM3)
    {
        return Density(kgM3);
    }
    FloatingType GetKgM3() const
    {
        return _kgM3;
    }

private:
    FloatingType _kgM3;
};
