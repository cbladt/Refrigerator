#pragma once

#include <atomic>

#include "Types.hpp"

class Fluid
{
public:
	Fluid() :
		_temperature(0),
		_pressure(0)
	{}
	~Fluid() = default;

	Fluid(const Fluid&) = default;
	Fluid& operator=(const Fluid&) = default;

	Fluid(Fluid&&) = default;
	Fluid& operator=(Fluid&&) = default;

	void SetTemperature(Kelvin temperature)
	{
		_temperature.store(temperature);
	}

	void SetPressure(BarAbsolute pressure)
	{
		if (pressure > 0)
		{
			_pressure.store(pressure);
		}
		else
		{
			throw "Fluid::SetPressure(): Negative Pressure";
		}
	}

	Kelvin GetTemperature() const
	{
		return _temperature.load();
	}

	BarAbsolute GetPressure() const
	{
		return _pressure.load();
	}

	DensityKgM3 GetDensity()
	{
		return 0;
	}

private:
	std::atomic<Kelvin> _temperature;
	std::atomic<BarAbsolute> _pressure;
};
