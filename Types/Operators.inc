Type operator+(const Type& a)
{
    return Value + a.Value;
}

Type operator-(const Type& a)
{
    return Value - a.Value;
}

Type operator*(const Type& a)
{
    return Value * a.Value;
}

Type operator/(const Type& a)
{
    return Value / a.Value;
}

bool operator>(const Type& a)
{
    return Value > a.Value;
}

bool operator<(const Type& a)
{
    return Value < a.Value;
}

Type(const Type& other)
{
    Value = other.Value;
}

Type& operator=(const Type& other)
{
    Value = other.Value;
    return *this;
}

Type(Type&& other)
{
    Value = other.Value;
}

Type operator=(Type&& other)
{
    Value = other.Value;
    return *this;
}
