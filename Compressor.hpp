#pragma once

#include "Container.hpp"
#include "Helpers/Map.hpp"

template <typename SuctionPort, typename DischargePort>
class Compressor
{
public:
	Compressor(Rpm minRpm, Rpm maxRpm, Percent efficiency, VolumeM3 volume, SuctionPort& suction, DischargePort& discharge) :
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
		auto rpm = Map<Rpm>(_capacity, PercentMin, PercentMax, _minRpm, _maxRpm);

		if (_capacity == 0)
		{
			rpm = 0;
		}

		// Ideal amount of suck.
		auto displacement = (_suction.GetFluid().GetDensity() * _volume * rpm);

		// Do the sucking.
		auto flow = _suction.Out(_suction.GetFluid().GetPressure() * displacement);

		// Do the blowing.
		_discharge.In(flow / _discharge.GetFluid().GetPressure());

		auto workW = flow * (_discharge.GetFluid().GetEnthalpy() - _suction.GetFluid().GetEnthalpy());
		workW *= (_efficiency / 100);
		auto workJ = workW / (rpm / 60);
		auto workKj = workJ / 1000;
		auto deltaTemperature = _discharge.GetFluid().GetTemperature() - _suction.GetFluid().GetTemperature();
		auto enthalpy = workKj / _volume * deltaTemperature;
		_discharge.GetFluid().AddEnthalpy(enthalpy);
		_suction.GetFluid().AddEnthalpy(enthalpy / -1);

		return flow;
	}

private:
	Rpm _minRpm;
	Rpm _maxRpm;	
	Percent _efficiency;
	VolumeM3 _volume;
	SuctionPort& _suction;
	DischargePort& _discharge;
	Percent _capacity;
};

