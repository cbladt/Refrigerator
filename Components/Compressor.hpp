#pragma once

#include <iostream>

#include <Types/Rpm.hpp>
#include <Types/Percent.hpp>
#include <Types/Enthropy.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Seconds.hpp>
#include <Types/Volume.hpp>

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

    auto Service(Seconds tick)
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

    auto GetRevolutionsPerSecond() const
    {
        return GetRpm() / 60;
    }

    auto Displace(Seconds tick)
    {        
        auto dSuc = _suction.GetFluid().GetGasDensity();
        auto pSuc = _suction.GetFluid().GetPressure();
        auto hSuc = _suction.GetFluid().GetEnthalpy();
        auto pDis = _discharge.GetFluid().GetPressure();

        auto timefactor = GetRevolutionsPerSecond() * tick;
        auto displacement = Volume::FromM3(dSuc.GetKgM3() * _volume.GetM3() * timefactor);

        auto flow = _suction.Out(pSuc.GetBar() * displacement.GetM3());
        _discharge.In(flow);

        if (flow > 0.00001)
        {
            auto enthropy = FluidCalculator::EnthropyFromEnthalpyAndPressure(hSuc, pSuc);
            //enthropy = Enthropy::FromJPrKgPrK(enthropy.GetJPrKgPrK() * 0.8);

            auto hDis = FluidCalculator::EnthalpyFromPressureAndEnthropy(pDis, enthropy);

            _discharge.GetFluid().SetEnthalpy(hDis);
        }

        return flow;
    }
};

