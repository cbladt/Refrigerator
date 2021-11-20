#pragma once

#include <Types/FloatingType.hpp>

class Percent
{
public:
    operator FloatingType() const
    {
        return _percent;
    }

    static const constexpr auto Min = 0;
    static const constexpr auto Max = 0;

private:
    FloatingType _percent;
};
