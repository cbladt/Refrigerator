#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Enthropy :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Enthropy(FloatingType jPrKgPrK) :
        NumericTypeBase(_jPrKgPrK),
        _jPrKgPrK(jPrKgPrK)
    {}

    Enthropy(const Enthropy& other) :
        NumericTypeBase(_jPrKgPrK)
    {
        _jPrKgPrK = other._jPrKgPrK;
    }

    Enthropy operator=(const Enthropy& other)
    {
        return Enthropy(other._jPrKgPrK);
    }

    Enthropy(Enthropy&& other) :
        NumericTypeBase(_jPrKgPrK)
    {
        _jPrKgPrK = other._jPrKgPrK;
    }

    Enthropy operator=(Enthropy&& other)
    {
        return Enthropy(other._jPrKgPrK);
    }


    static constexpr Enthropy FromJPrKgPrK(FloatingType jPrKgPrK)
    {
        return Enthropy(jPrKgPrK);
    }
    FloatingType GetJPrKgPrK() const
    {
        return _jPrKgPrK;
    }

private:
    FloatingType _jPrKgPrK;
};
