#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Temperature :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Temperature(FloatingType kelvin) :
        NumericTypeBase(_kelvin),
        _kelvin(kelvin)
    {}

    Temperature(const Temperature& other) :
        NumericTypeBase(_kelvin)
    {
        _kelvin = other._kelvin;
    }

    Temperature operator=(const Temperature& other)
    {
        return Temperature(other._kelvin);
    }

    Temperature(Temperature&& other) :
        NumericTypeBase(_kelvin)
    {
        _kelvin = other._kelvin;
    }

    Temperature operator=(Temperature&& other)
    {
        return Temperature(other._kelvin);
    }


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
