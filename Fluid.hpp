#pragma once

#include <atomic>
#include <limits>

#include "Types.hpp"
#include "Helpers/Limit.hpp"

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


	void SetPressure(Pressure pressure)
	{
		pressure = Limit<Pressure>(pressure, 0, std::numeric_limits<Pressure>::max());
		_pressure.store(pressure);
	}

	Pressure GetPressure() const
	{
		return _pressure.load();
	}


	void SetEnthalpy(Enthalpy enthalpy)
	{
		enthalpy = Limit<Enthalpy>(enthalpy, 0, std::numeric_limits<Enthalpy>::max());
		_enthalpy.store(enthalpy);
	}

	void AddEnthalpy(Enthalpy enthalpy)
	{
		SetEnthalpy(enthalpy + _enthalpy.load());
	}

	Enthalpy GetEnthalpy() const
	{
		return _enthalpy.load();
	}


	Density GetDensity()
	{
		return 1;
	}

	Temperature GetTemperature() const
	{
		return _temperature.load();
	}

private:
	std::atomic<Temperature> _temperature;
	std::atomic<Pressure> _pressure;
	std::atomic<Enthalpy> _enthalpy;
};
