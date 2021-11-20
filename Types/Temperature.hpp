#pragma once

#include <Types/FloatingType.hpp>

class Temperature
{
private:
    constexpr Temperature(FloatingType kelvin) :
        _kelvin(kelvin)
    {}

    FloatingType _kelvin;

public:
    static constexpr Temperature FromKelvin(FloatingType kelvin)
    {
        return Temperature(kelvin);
    }
    FloatingType GetKelvin() const
    {
        return _kelvin;
    }
};
