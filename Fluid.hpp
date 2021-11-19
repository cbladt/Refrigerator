#pragma once

#include <atomic>
#include <limits>

#include "CoolProp.h"

#include "Types.hpp"
#include "Helpers/Limit.hpp"

class Fluid
{
public:
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
		return CoolProp::PropsSI("D", "T|gas", GetTemperatureK(), "P", GetPressure() * BarAbsoluteToPascal, "HEOS::R134A");
	}

	Density GetLiquidDensity()
	{
		return 1;
	}

	Temperature GetTemperatureK() const
	{
		auto enthalpyInJoulePrKg = GetEnthalpy() * EnthalpyKjPrKgToJPrKg;
		auto pressureInPascal = GetPressure() * BarAbsoluteToPascal;
		return CoolProp::PropsSI("T", "P", pressureInPascal, "H", enthalpyInJoulePrKg, "HEOS::R134A");
	}

private:
	std::atomic<Pressure> _pressure;
	std::atomic<Enthalpy> _enthalpy;
};
