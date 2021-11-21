#pragma once

#include <iostream>

#include <Types/Rpm.hpp>
#include <Types/Percent.hpp>
#include <Types/Enthropy.hpp>
#include <Types/Enthalpy.hpp>

#include "Container.hpp"
#include "Helpers/Map.hpp"

template <typename SuctionPort, typename DischargePort>
class Compressor
{
public:
    using FluidCalculator = typename SuctionPort::Fluid::Calculator;

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
        auto suctionEnthalpy = _suction.GetFluid().GetEnthalpy();
        auto suctionPressure = _suction.GetFluid().GetPressure();

		auto flow = DoDisplacement();

        auto enthropy = EnthropyCalculation(suctionEnthalpy, suctionPressure);

		auto enthalpy = EnthalpyCalculation(enthropy);

        _suction.GetFluid().SubtractEnthalpy(enthalpy);
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
        auto rpm = Map<Rpm>(_capacity, Percent::Min, Percent::Max, _minRpm, _maxRpm);

                if (_capacity == 0)
                {
                        rpm = 0;
                }

		return rpm;
	}

	auto DoDisplacement()
	{
        auto density = _suction.GetFluid().GetGasDensity().GetKgM3();
        auto displacement = Volume::FromM3(density * _volume.GetM3() * GetRpm());
        auto flow = _suction.Out(_suction.GetFluid().GetPressure().GetBar() * displacement.GetM3());
        _discharge.In(flow.GetKg() / _discharge.GetFluid().GetPressure().GetBar());

		return flow;
	}

    auto EnthropyCalculation(Enthalpy enthalpy, Pressure pressure)
	{
        auto enthropy = FluidCalculator::EnthropyFromEnthalpyAndPressure(enthalpy, pressure);
        enthropy = Enthropy::FromJPrKgPrK(enthropy.GetJPrKgPrK() * 0.8);

        std::cout << "enthropy " << std::to_string(enthropy.GetJPrKgPrK()) << std::endl;

		return enthropy;
	}

    auto EnthalpyCalculation(Enthropy enthropy)
	{
        auto enthalpy = FluidCalculator::EnthalpyFromPressureAndEnthropy(_discharge.GetFluid().GetPressure(), enthropy);

        std::cout << "enthalpy " << std::to_string(enthalpy.GetKjPrKg()) << std::endl;

		return enthalpy;
	}
};

