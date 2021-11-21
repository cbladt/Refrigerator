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
        if (pressure.GetBar() > 0)
        {
            _pressure = pressure;
        }
        else
        {
            _pressure = 0;
        }
	}

	Pressure GetPressure() const
	{
        return _pressure;
	}


	void SetEnthalpy(Enthalpy enthalpy)
	{
        if (enthalpy.GetKjPrKg() > 0)
        {
            _enthalpy = enthalpy;
        }
        else
        {
            _enthalpy = 0;
        }
	}

	void AddEnthalpy(Enthalpy enthalpy)
	{                                   
        SetEnthalpy(enthalpy + _enthalpy);
	}

    void SubtractEnthalpy(Enthalpy enthalpy)
    {
        SetEnthalpy(enthalpy - _enthalpy);
    }

	Enthalpy GetEnthalpy() const
	{
        return _enthalpy;
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
    Pressure _pressure;
    Enthalpy _enthalpy;
};
