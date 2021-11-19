#pragma once

#include <atomic>

#include "Types.hpp"

class Fluid
{
public:
	Fluid() :
		_temperature(0),
		_pressure(0),
		_enthalpy(0)
	{}
	~Fluid() = default;

	Fluid(const Fluid&) = default;
	Fluid& operator=(const Fluid&) = default;

	Fluid(Fluid&&) = default;
	Fluid& operator=(Fluid&&) = default;


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

	BarAbsolute GetPressure() const
	{
		return _pressure.load();
	}


	void SetEnthalpy(EnthalpyKjKg enthalpy)
	{
		if (enthalpy > 0)
		{
			_enthalpy.store(enthalpy);
		}
		else
		{
			throw "Fluid::SetEnthalpy(): Negative Enthalpy";
		}

	}

	void AddEnthalpy(EnthalpyKjKg enthalpy)
	{
		_enthalpy.store(enthalpy + _enthalpy.load());
	}

	EnthalpyKjKg GetEnthalpy() const
	{
		return _enthalpy.load();
	}


	DensityKgM3 GetDensity()
	{
		return 1;
	}

	Kelvin GetTemperature() const
	{
		return _temperature.load();
	}

private:
	std::atomic<Kelvin> _temperature;
	std::atomic<BarAbsolute> _pressure;
	std::atomic<EnthalpyKjKg> _enthalpy;
};
