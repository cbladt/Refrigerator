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

Type operator=(const Type& other)
{
    return Type(other.Value);
}

Type(Type&& other)
{
    Value = other.Value;
}

Type operator=(Type&& other)
{
    return Type(other.Value);
}
