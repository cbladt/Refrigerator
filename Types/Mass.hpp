#pragma once

#include <Types/FloatingType.hpp>

class Mass
{
private:
    constexpr Mass(FloatingType kg) :
        _kg(kg)
    {}

    FloatingType _kg;

public:
    bool operator>(Mass a)
    {
        return _kg > a._kg;
    }

    Mass operator-(Mass a)
    {
        return Mass(_kg - a._kg);
    }

    Mass operator+(Mass a)
    {
        return Mass(_kg + a._kg);
    }

    static constexpr Mass FromKg(FloatingType kg)
    {
        return Mass(kg);
    }
    FloatingType GetKg() const
    {
        return _kg;
    }
};
