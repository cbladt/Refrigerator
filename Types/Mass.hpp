#pragma once

#include <Types/FloatingType.hpp>

class Mass
{
public:
    constexpr Mass(FloatingType kg) :
        _kg(kg)
    {}

#define Type Mass
#define Value _kg
#include <Types/Operators.inc>
#undef Value
#undef Type

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
