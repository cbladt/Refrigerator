#pragma once

template <typename T>
T Limit(T in, T min, T max)
{
	if (in > max)
	{
		return max;
	}

	if (in < min)
	{
		return min;
	}

	return in;
}
