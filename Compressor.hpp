#pragma once

#include "Container.hpp"
#include "Helpers/Map.hpp"

template <typename SuctionPort, typename DischargePort>
class Compressor
{
public:
	Compressor(Rpm minRpm, Rpm maxRpm, VolumeM3 volume, SuctionPort& suction, DischargePort& discharge) :
		_minRpm(minRpm),
		_maxRpm(maxRpm),
		_volume(volume),
		_suction(suction),
		_discharge(discharge),
		_capacity(0)
	{}

	void Service()
	{
		Displace();
	}

	void SetCapacity(Percent capacity)
	{
		_capacity = capacity;
	}

	void Displace()
	{
		auto rpm = Map<Rpm>(_capacity, Percent::Min, Percent::Max, _minRpm, _maxRpm);
		auto displacementM3 = (_suction.GetDensity() * _volume * rpm);

		_suction.Out(_suction.GetFluid().GetPressure() * _volume);

		_discharge.In(_discharge.GetMass() / _discharge.GetFluid().GetPressure());
	}

private:
	Rpm _minRpm;
	Rpm _maxRpm;
	VolumeM3 _volume;
	SuctionPort& _suction;
	DischargePort& _discharge;
	Percent _capacity;
};

