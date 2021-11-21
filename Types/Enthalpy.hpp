#pragma once

#include <Types/FloatingType.hpp>

class Enthalpy
{
public:
    constexpr Enthalpy(FloatingType jPrG) :
        _jPrG(jPrG)
    {}

#define Type Enthalpy
#define Value _jPrG
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Enthalpy FromJPrG(FloatingType jPrG)
    {
        return Enthalpy(jPrG);
    }
    FloatingType GetJPrG() const
    {
        return _jPrG;
    }

    static constexpr Enthalpy FromKjPrKg(FloatingType kjPrKg)
    {
        return Enthalpy(kjPrKg * 1);
    }
    FloatingType GetKjPrKg() const
    {
        return _jPrG * 1;
    }

    static constexpr Enthalpy FromJPrKg(FloatingType jPrKg)
    {
        return Enthalpy(jPrKg / 1000);
    }
    FloatingType GetJPrKg() const
    {
        return _jPrG * 1000;
    }

private:
    FloatingType _jPrG;
};
