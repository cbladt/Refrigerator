#pragma once

#include <Types/FloatingType.hpp>
#include <Types/NumericTypeBase.hpp>

class Volume :
        public NumericTypeBase<FloatingType>
{
public:
    constexpr Volume(FloatingType m3) :
        NumericTypeBase(_m3),
        _m3(m3)
    {}

    Volume(const Volume& other) :
        NumericTypeBase(_m3)
    {
        _m3 = other._m3;
    }

    Volume operator=(const Volume& other)
    {
        return Volume(other._m3);
    }

    Volume(Volume&& other) :
        NumericTypeBase(_m3)
    {
        _m3 = other._m3;
    }

    Volume operator=(Volume&& other)
    {
        return Volume(other._m3);
    }


    static constexpr Volume FromM3(FloatingType m3)
    {
        return Volume(m3);
    }
    FloatingType GetM3() const
    {
        return _m3;
    }

private:
    FloatingType _m3;
};
