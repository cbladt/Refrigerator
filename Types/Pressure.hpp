#pragma once

#include <Types/FloatingType.hpp>

class Pressure
{
public:
    constexpr Pressure(FloatingType pascal) :
        _pascal(pascal)
    {}

#define Type Pressure
#define Value _pascal
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Pressure FromPascal(FloatingType pascal)
    {
        return Pressure(pascal);
    }
    FloatingType GetPascal() const
    {
        return _pascal;
    }

    static constexpr Pressure FromBar(FloatingType bar)
    {
        return Pressure(bar * 100000);
    }
    FloatingType GetBar() const
    {
        return _pascal / 100000;
    }

private:
    FloatingType _pascal;
};
