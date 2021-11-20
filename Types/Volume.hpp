#pragma once

#include <Types/FloatingType.hpp>

class Volume
{
private:
    constexpr Volume(FloatingType m3) :
        _m3(m3)
    {}

    FloatingType _m3;

public:
    static constexpr Volume FromM3(FloatingType m3)
    {
        return Volume(m3);
    }
    FloatingType GetM3() const
    {
        return _m3;
    }
};
