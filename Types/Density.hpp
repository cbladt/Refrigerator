#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Density :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Density(FloatingType kgM3) :
        NumericTypeBase(_kgM3),
        _kgM3(kgM3)
    {}

    Density(const Density& other) :
        NumericTypeBase(_kgM3)
    {
        _kgM3 = other._kgM3;
    }

    Density operator=(const Density& other)
    {
        return Density(other._kgM3);
    }

    Density(Density&& other) :
        NumericTypeBase(_kgM3)
    {
        _kgM3 = other._kgM3;
    }

    Density operator=(Density&& other)
    {
        return Density(other._kgM3);
    }


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
