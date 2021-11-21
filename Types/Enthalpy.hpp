#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Enthalpy :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Enthalpy(FloatingType jPrG) :
        NumericTypeBase(_jPrG),
        _jPrG(jPrG)
    {}

    Enthalpy(const Enthalpy& other) :
        NumericTypeBase(_jPrG)
    {
        _jPrG = other._jPrG;
    }

    Enthalpy operator=(const Enthalpy& other)
    {
        return Enthalpy(other._jPrG);
    }

    Enthalpy(Enthalpy&& other) :
        NumericTypeBase(_jPrG)
    {
        _jPrG = other._jPrG;
    }

    Enthalpy operator=(Enthalpy&& other)
    {
        return Enthalpy(other._jPrG);
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

private:
    FloatingType _jPrG;
};
