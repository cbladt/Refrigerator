#pragma once

#include <Types/FloatingType.hpp>

class Pressure
{
public:
private:
    constexpr Pressure(FloatingType pascal) :
        _pascal(pascal)
    {}

    FloatingType _pascal;

public:
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
};
