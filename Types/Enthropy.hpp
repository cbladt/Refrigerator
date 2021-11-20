#pragma once

#include <Types/FloatingType.hpp>

class Enthropy
{
private:
    constexpr Enthropy(FloatingType jPrKgPrK) :
        _jPrKgPrK(jPrKgPrK)
    {}

    FloatingType _jPrKgPrK;

public:
    static constexpr Enthropy FromJPrKgPrK(FloatingType jPrKgPrK)
    {
        return Enthropy(jPrKgPrK);
    }
    FloatingType GetJPrKgPrK() const
    {
        return _jPrKgPrK;
    }
};
