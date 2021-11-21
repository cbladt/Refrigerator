#pragma once

#include <Types/FloatingType.hpp>

class Percent :
        public NumericTypeBase<FloatingType>
{
public:
    Percent(FloatingType percent) :
        NumericTypeBase(_percent),
        _percent(percent)
    {}

    operator FloatingType() const
    {
        return _percent;
    }

    void operator=(const Percent& other)
    {
        _percent = other._percent;
    }

    static const constexpr auto Min = 0;
    static const constexpr auto Max = 0;

private:
    FloatingType _percent;
};
