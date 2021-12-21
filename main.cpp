#include <iostream>
#include <thread>
#include <chrono>

#include <Helpers/Limit.hpp>

#include <Types/FloatingType.hpp>
#include <Types/Volume.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Pressure.hpp>

#include <Components/Compressor.hpp>
#include <Components/Container.hpp>
#include <Components/ExpansionValve.hpp>

#include <FluidCalculator.hpp>

static const constexpr FloatingType CompressorCylinders = 4;
static const constexpr FloatingType CompressorBoreMm = 55;
static const constexpr FloatingType CompressorStrokeMm = 39.3;
static const constexpr FloatingType CompressorSingleCylinderVolume = 3.14f * (CompressorBoreMm*CompressorBoreMm) * CompressorStrokeMm;
static Volume CompressorVolume = Volume::FromMm3(CompressorCylinders * CompressorSingleCylinderVolume);

static Enthalpy InitialDischargeEnthalpy = Enthalpy::FromKjPrKg(480);
static Pressure InitialDischargePressure = Pressure::FromBar(6);

static Enthalpy InitialSuctionEnthalpy = Enthalpy::FromKjPrKg(380);
static Pressure InitialSuctionPressure = Pressure::FromBar(3);

using Calculator_t = FluidCalculator<1341>;
using Fluid_t = Fluid<Calculator_t>;
using Container_t = Container<Fluid_t>;

template <auto LengthCm, auto DiameterCm>
static constexpr auto PipeVolume()
{
    auto radius = static_cast<FloatingType>(DiameterCm)/2.f;
    auto volume = LengthCm * (3.14f * (radius * radius));
    return Volume::FromCm3(volume);
}

int main()
{    
    Container_t suction(PipeVolume<1000, 25>(), Mass::FromKg(0));
    Container_t discharge(PipeVolume<1000, 25>(), Mass::FromKg(0));

    Compressor compressor(1000, 3000, Percent(80), CompressorVolume, suction, discharge);
    compressor.SetCapacity(100);

    suction.GetFluid().SetEnthalpy(InitialSuctionEnthalpy);
    suction.GetFluid().SetPressure(InitialSuctionPressure);
    suction.SetMassFromPressure(InitialSuctionPressure);

    discharge.GetFluid().SetEnthalpy(InitialDischargeEnthalpy);
    discharge.GetFluid().SetPressure(InitialDischargePressure);
    discharge.SetMassFromPressure(InitialDischargePressure);

    ExpansionValve valve(0, 5000, discharge, suction);
    float signal = 50;

    auto debug = [&](auto flow)
    {
        std::cout << "-- -- --" << std::endl;
        //std::cout << "Flow\t" << std::to_string(flow.GetKg()) << std::endl;
        std::cout << "PSuc\t" << std::to_string(suction.GetFluid().GetPressure().GetBar()) << std::endl;
        std::cout << "TSuc\t" << std::to_string(suction.GetFluid().GetTemperature().GetCelcius()) << std::endl;
        std::cout << "HSuc\t" << std::to_string(suction.GetFluid().GetEnthalpy().GetKjPrKg()) << std::endl;
        std::cout << "MSuc\t" << std::to_string(suction.GetMass().GetKg()) << std::endl;
        std::cout << std::endl;
        std::cout << "PDis\t" << std::to_string(discharge.GetFluid().GetPressure().GetBar()) << std::endl;
        std::cout << "TDis\t" << std::to_string(discharge.GetFluid().GetTemperature().GetCelcius()) << std::endl;
        std::cout << "HDis\t" << std::to_string(discharge.GetFluid().GetEnthalpy().GetKjPrKg()) << std::endl;
        std::cout << "MDis\t" << std::to_string(discharge.GetMass().GetKg()) << std::endl;

        std::cout << "Valve\t" << std::to_string(signal) << std::endl;
    };

    debug(Mass::FromKg(0));

    for (auto n = 0; n < 3001; n++)
    {
        auto error = 2 - suction.GetFluid().GetPressure().GetBar();
        signal += error * 0.2;
        signal = Limit<float>(signal, 0, 100);
        valve.SetSignal(signal);

        auto flow = compressor.Service(1);
        valve.Service(1);

        if (n % 250 == 0)
        {
            debug(flow);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}
