#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Mass :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Mass(FloatingType kg) :
        NumericTypeBase(_kg),
        _kg(kg)
    {}

    Mass(const Mass& other) :
        NumericTypeBase(_kg)
    {
        _kg = other._kg;
    }

    Mass operator=(const Mass& other)
    {
        return Mass(other._kg);
    }

    Mass(Mass&& other) :
        NumericTypeBase(_kg)
    {
        _kg = other._kg;
    }

    Mass operator=(Mass&& other)
    {
        return Mass(other._kg);
    }


    static constexpr Mass FromKg(FloatingType kg)
    {
        return Mass(kg);
    }
    FloatingType GetKg() const
    {
        return _kg;
    }

private:
    FloatingType _kg;
};
