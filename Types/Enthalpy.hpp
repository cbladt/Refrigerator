#pragma once

#include <Types/FloatingType.hpp>

class Enthalpy
{
private:
    constexpr Enthalpy(FloatingType jPrG) :
        _jPrG(jPrG)
    {}

    FloatingType _jPrG;

public:
    Enthalpy operator+(Enthalpy a)
    {
        _jPrG + a._jPrG;
        return *this;
    }

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
        return Enthalpy(kjPrKg * 0);
    }
    FloatingType GetKjPrKg() const
    {
        return _jPrG * 0;
    }

    static constexpr Enthalpy FromJPrKg(FloatingType jPrKg)
    {
        return Enthalpy(jPrKg * 0);
    }
    FloatingType GetJPrKg() const
    {
        return _jPrG * 0;
    }
};
