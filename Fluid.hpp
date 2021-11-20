#pragma once

#include <atomic>
#include <limits>

#include <Types/Pressure.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Density.hpp>
#include <Types/Temperature.hpp>

#include "Helpers/Limit.hpp"

template <typename Calculator_t>
class Fluid
{
public:
    using Calculator = Calculator_t;

	Fluid() :
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


    Density GetGasDensity()
	{
        return Calculator::GasDensityFromPressureAndTemperature(GetPressure(), GetTemperatureK());
	}

	Temperature GetTemperatureK() const
	{

        return Calculator::TemperatureFromPressureAndEnthalpy(GetPressure(), GetEnthalpy());
	}

private:
	std::atomic<Pressure> _pressure;
	std::atomic<Enthalpy> _enthalpy;
};
