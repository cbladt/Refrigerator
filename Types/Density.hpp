#pragma once

#include <Types/FloatingType.hpp>

class Density
{
private:
    constexpr Density(FloatingType kgM3) :
        _kgM3(kgM3)
    {}

    FloatingType _kgM3;

public:
    static constexpr Density FromKgM3(FloatingType kgM3)
    {
        return Density(kgM3);
    }
    FloatingType GetKgM3() const
    {
        return _kgM3;
    }
};
