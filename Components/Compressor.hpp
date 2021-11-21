#pragma once

#include <iostream>

#include <Types/Rpm.hpp>
#include <Types/Percent.hpp>
#include <Types/Enthropy.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Milliseconds.hpp>

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

    auto Service(Milliseconds tick)
    {
        return Displace(tick);
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

    auto Displace(Milliseconds tick)
    {
        auto suctionEnthalpy = _suction.GetFluid().GetEnthalpy();
        auto suctionPressure = _suction.GetFluid().GetPressure();
        auto suctionDensity = _suction.GetFluid().GetGasDensity();

        auto rpm = (GetRpm() / 60 / 1000) * tick;
        auto flowPrMs = Volume::FromM3(suctionDensity.GetKgM3() * _volume.GetM3() * rpm);

        auto displacement = flowPrMs * Volume::FromM3(tick);

        auto flow = _suction.Out(_suction.GetFluid().GetPressure().GetBar() * displacement.GetM3());
        _discharge.In(flow.GetKg() / _discharge.GetFluid().GetPressure().GetBar());

        auto enthropy = FluidCalculator::EnthropyFromEnthalpyAndPressure(suctionEnthalpy, suctionPressure);
        enthropy = Enthropy::FromJPrKgPrK(enthropy.GetJPrKgPrK() * 0.8);

        auto enthalpy = FluidCalculator::EnthalpyFromPressureAndEnthropy(_discharge.GetFluid().GetPressure(), enthropy);

        _suction.GetFluid().SubtractEnthalpy(enthalpy);
        _discharge.GetFluid().AddEnthalpy(enthalpy);

        return flow;
    }
};

