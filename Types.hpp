#pragma once

#include "Helpers/Limit.hpp"

using FloatingType = float;

using Kelvin = FloatingType;
using BarAbsolute = FloatingType;
using DensityKgM3 = FloatingType;
using Rpm = FloatingType;
using VolumeM3 = FloatingType;
using Mass = FloatingType;

class Percent
{
	using Percent_t = FloatingType;
	const constexpr static auto Min = 0;
	const constexpr static auto Max = 100;

	Percent_t Get()
	{
		return _value;
	}

	void Set(Percent_t value)
	{
		_value = Limit<Percent_t>(value, Min, Max);
	}

	operator const Percent_t()
	{
		return Get();
	}

	operator Percent_t()
	{
		return Get();
	}

private:
	Percent_t _value;
};
