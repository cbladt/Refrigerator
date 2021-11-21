#pragma once

#include <Types/FloatingType.hpp>

class Volume
{
public:
    constexpr Volume(FloatingType m3) :
        _m3(m3)
    {}

#define Type Volume
#define Value _m3
#include <Types/Operators.inc>
#undef Value
#undef Type

    static constexpr Volume FromM3(FloatingType m3)
    {
        return Volume(m3);
    }
    FloatingType GetM3() const
    {
        return _m3;
    }

    static constexpr Volume FromMm3(FloatingType mm3)
    {
        return Volume(mm3 / 1000000000);
    }
    FloatingType GetMm3() const
    {
        return _m3 * 1000000000;
    }

private:
    FloatingType _m3;
};
