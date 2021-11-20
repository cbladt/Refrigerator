#include <iostream>

#include <Types/FloatingType.hpp>
#include <Types/Volume.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Pressure.hpp>

#include <Components/Compressor.hpp>
#include <Components/Container.hpp>

#include <FluidCalculator.hpp>

static const constexpr FloatingType CompressorCylinders = 1;
static const constexpr FloatingType CompressorBoreMm = 55;
static const constexpr FloatingType CompressorStrokeMm = 39.3;
static const constexpr Volume CompressorVolume = Volume::FromM3(CompressorCylinders * ((3.14f * (CompressorBoreMm*CompressorBoreMm) * CompressorStrokeMm) / 1000000000));

static const constexpr Enthalpy InitialDischargeEnthalpy = Enthalpy::FromKjPrKg(260);
static const constexpr Pressure InitialDischargePressure = Pressure::FromBar(6);

static const constexpr Enthalpy InitialSuctionEnthalpy = Enthalpy::FromKjPrKg(400);
static const constexpr Pressure InitialSuctionPressure = Pressure::FromBar(4);

using Calculator_t = FluidCalculator<1341>;
using Fluid_t = Fluid<Calculator_t>;
using Container_t = Container<Fluid_t>;

template <auto LengthCm, auto DiameterCm>
static constexpr auto PipeVolume()
{
    auto radius = static_cast<FloatingType>(DiameterCm)/2.f;
    auto volume = LengthCm * (3.14f * (radius * radius));
    return Volume::FromM3(volume);
}

int main()
{    
    Container_t suction(PipeVolume<100, 10>(), Mass::FromKg(30000));
    Container_t discharge(PipeVolume<100, 10>(), Mass::FromKg(70000));
    /*Container afterCondensor(PipeVolume<30, 1>());
    Container beforeEvaporator(PipeVolume<10, 1>());*/

    Compressor compressor(1000, 3000, 80, CompressorVolume, suction, discharge);
    compressor.SetCapacity(1);

    suction.GetFluid().SetEnthalpy(InitialSuctionEnthalpy);
    suction.GetFluid().SetPressure(InitialSuctionPressure);

    //afterCondensor.GetFluid().SetTemperature(InitialSuctionTemperature);
    //afterCondensor.GetFluid().SetPressure(InitialSuctionPressure);

    discharge.GetFluid().SetEnthalpy(InitialDischargeEnthalpy);
    discharge.GetFluid().SetPressure(InitialDischargePressure);

    //afterCondensor.GetFluid().SetTemperature(InitialDischargeTemperature);
    //afterCondensor.GetFluid().SetPressure(InitialDischargePressure);

    auto debug = [&](auto flow)
    {
        std::cout << "PSuc\t" << std::to_string(suction.GetFluid().GetPressure().GetBar()) << std::endl;
        std::cout << "HSuc\t" << std::to_string(suction.GetFluid().GetEnthalpy().GetKjPrKg()) << std::endl;
        std::cout << "PDis\t" << std::to_string(discharge.GetFluid().GetPressure().GetBar()) << std::endl;
        std::cout << "HDis\t" << std::to_string(discharge.GetFluid().GetEnthalpy().GetKjPrKg()) << std::endl;
        std::cout << "Flow\t" << std::to_string(flow) << std::endl << std::endl;
    };

    debug(-1);

    for (auto n = 0; n < 2; n++)
    {
        auto flow = compressor.Displace();

        //if (n % 1000 == 0)
        {
            debug(flow);
        }
    }

    return 0;
}
