#pragma once

template <typename T>
class NumericTypeBase
{
public:
    constexpr NumericTypeBase(T& underlyingVariable) :
        _v(underlyingVariable)
    {}

    ~NumericTypeBase() = default;

    NumericTypeBase operator+(const NumericTypeBase& a)
    {
        return _v + a._v;
    }

    NumericTypeBase operator-(const NumericTypeBase& a)
    {
        return _v - a._v;
    }

    NumericTypeBase operator*(const NumericTypeBase& a)
    {
        return _v * a._v;
    }

    NumericTypeBase operator/(const NumericTypeBase& a)
    {
        return _v / a._v;
    }

    NumericTypeBase operator%(const NumericTypeBase& a)
    {
        return _v % a._v;
    }

    bool operator>(const NumericTypeBase& a)
    {
        return _v > a._v;
    }

    bool operator<(const NumericTypeBase& a)
    {
        return _v < a._v;
    }

private:
    T& _v;
};
