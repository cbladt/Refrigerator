#pragma once

#include "Types.hpp"
#include "Fluid.hpp"

class Container
{
public:
	Container(Volume volume, Mass initialMass) :
		_volume(volume)
	{
		SetMass(initialMass);
	}
	~Container() = default;

	Container(const Container&) = delete;
	Container operator=(const Container&) = delete;

	Container(Container&&) = delete;
	Container operator=(Container&&) = delete;

	Mass Out(Mass request)
	{
		if (request > _mass)
		{
			request = _mass;
		}

		if ((_mass - request) > 0.000001f)
		{
			SetMass(_mass - request);
		}
		else
		{
			return request;
		}
	}

	void In(Mass request)
	{
		SetMass(_mass + request);
	}

	Mass GetMass() const
	{
		return _mass;
	}

	Fluid& GetFluid()
	{
		return _fluid;
	}

private:
	Volume _volume;
	Mass _mass;
	Fluid _fluid;

	void SetMass(Mass newMass)
	{
		_mass = newMass;
		_fluid.SetPressure(_mass / _volume);
	}
};
