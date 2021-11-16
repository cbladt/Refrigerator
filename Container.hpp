#pragma once

#include "Types.hpp"
#include "Fluid.hpp"

template <VolumeM3 Volume>
class Container
{
	Container() :
		_mass(0),
		_pressure(0)
	{}
	~Container() = default;

	Container(const Container&) = delete;
	Container operator=(const Container&) = delete;

	Container(Container&&) = delete;
	Container operator=(Container&&) = delete;

	Mass Out(Mass request)
	{
		if (request > _mass)
		{
			request = _mass
		}

		SetMass(_mass - request);

		return request;
	}

	void In(Mass request)
	{
		SetMass(_mass + request);
	}

	Mass GetMass() const
	{
		return _mass:
	}

	Fluid GetFluid() const
	{
		return _fluid;
	}

private:
	Mass _mass;
	Fluid _fluid;

	void SetMass(Mass newMass)
	{
		_mass = newMass;
		_fluid.SetPressure(_mass / Volume);
	}
};
