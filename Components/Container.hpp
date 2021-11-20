#pragma once

#include <Types/Mass.hpp>
#include <Types/Volume.hpp>

#include <Fluid.hpp>

template <typename Fluid_t>
class Container
{
public:
    using Fluid = Fluid_t;

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
            return 0;
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

    void SetMass(Mass& newMass)
	{
		_mass = newMass;
        _fluid.SetPressure(Pressure::FromBar(_mass.GetKg() / _volume.GetM3()));
	}
};
