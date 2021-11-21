#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Pressure :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Pressure(FloatingType pascal) :
        NumericTypeBase(_pascal),
        _pascal(pascal)
    {}

    Pressure(const Pressure& other) :
        NumericTypeBase(_pascal)
    {
        _pascal = other._pascal;
    }

    Pressure operator=(const Pressure& other)
    {
        return Pressure(other._pascal);
    }

    Pressure(Pressure&& other) :
        NumericTypeBase(_pascal)
    {
        _pascal = other._pascal;
    }

    Pressure operator=(Pressure&& other)
    {
        return Pressure(other._pascal);
    }


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
