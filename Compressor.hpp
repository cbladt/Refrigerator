#pragma once

#include "Container.hpp"

template <Rpm Min, Rpm Max, VolumeM3 Volume, typename SuctionPort, typename DischargePort>
class Compressor
{
public:
	Compressor(SuctionPort suction, DischargePort discharge) :
		_suction(suction),
		_discharge(discharge)
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
		auto rpm = Map<Rpm, _capacity, Percent::Min, Percent::Max, Min, Max);
		auto displacementM3 = (_suction.GetDensity() * Volume * rpm);

		_suction.Out(_suction.GetFluid().GetPressure() * Volume);

		_discharge.In(_discharge.GetMass() / _discharge.GetFluid().GetPressure());
	}

private:
	SuctionPort _suction;
	DischargePort _discharge;
	Percent _capacity;
};

