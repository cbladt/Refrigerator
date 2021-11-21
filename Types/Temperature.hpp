#pragma once

#include <Types/FloatingType.hpp>

class Temperature
{
public:
    constexpr Temperature(FloatingType kelvin) :
        _kelvin(kelvin)
    {}

#define Type Temperature
#define Value _kelvin
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Temperature FromKelvin(FloatingType kelvin)
    {
        return Temperature(kelvin);
    }
    FloatingType GetKelvin() const
    {
        return _kelvin;
    }

private:
    FloatingType _kelvin;
};
