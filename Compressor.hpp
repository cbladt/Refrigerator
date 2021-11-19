#pragma once

#include <iostream>

#include "CoolProp.h"

#include "Container.hpp"
#include "Helpers/Map.hpp"

template <typename SuctionPort, typename DischargePort>
class Compressor
{
public:
	Compressor(Rpm minRpm, Rpm maxRpm, Percent efficiency, Volume volume, SuctionPort& suction, DischargePort& discharge) :
		_minRpm(minRpm),
		_maxRpm(maxRpm),
		_efficiency(efficiency),
		_volume(volume),
		_suction(suction),
		_discharge(discharge),
		_capacity(0)
	{}

	void SetCapacity(Percent capacity)
	{
		_capacity = capacity;
	}

	auto Displace()
	{

		auto suctionEnthalpyInJoulePrKg = _suction.GetFluid().GetEnthalpy() * EnthalpyKjPrKgToJPrKg;
		auto suctionPressureInPascal = _suction.GetFluid().GetPressure() * BarAbsoluteToPascal;

		auto flow = DoDisplacement();

		auto enthropy = EnthropyCalculation(suctionEnthalpyInJoulePrKg, suctionPressureInPascal);

		auto enthalpy = EnthalpyCalculation(enthropy);

		_suction.GetFluid().AddEnthalpy(enthalpy / -1);
		_discharge.GetFluid().AddEnthalpy(enthalpy);

		return flow;
	}

private:
	Rpm _minRpm;
	Rpm _maxRpm;	
	Percent _efficiency;
	Volume _volume;
	SuctionPort& _suction;
	DischargePort& _discharge;
	Percent _capacity;

	auto GetRpm() const
	{
		auto rpm = Map<Rpm>(_capacity, PercentMin, PercentMax, _minRpm, _maxRpm);

                if (_capacity == 0)
                {
                        rpm = 0;
                }

		return rpm;
	}

	auto DoDisplacement()
	{
		auto displacement = (_suction.GetFluid().GetDensity() * _volume * GetRpm());
		auto flow = _suction.Out(_suction.GetFluid().GetPressure() * displacement);
		_discharge.In(flow / _discharge.GetFluid().GetPressure());

		return flow;
	}

	template<typename T1, typename T2>
	auto EnthropyCalculation(T1 suctionEnthalpyInJoulePrKg, T2 suctionPressureInPascal)
	{
		auto enthropy = CoolProp::PropsSI("S", "H", suctionEnthalpyInJoulePrKg, "P", suctionPressureInPascal, "HEOS::R134A");
		enthropy *= (_efficiency / 100);

		std::cout << "enthropy " << std::to_string(enthropy) << std::endl;

		return enthropy;
	}

	template<typename T1>
	auto EnthalpyCalculation(T1 enthropy)
	{
		auto dischargePressureInPascal = _discharge.GetFluid().GetPressure() * BarAbsoluteToPascal;
		auto enthalpy = CoolProp::PropsSI("H", "P", dischargePressureInPascal, "S", enthropy, "HEOS::R134A") / EnthalpyKjPrKgToJPrKg;

		std::cout << "enthalpy " << std::to_string(enthalpy) << std::endl;

		return enthalpy;
	}
};

