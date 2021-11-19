#include <iostream>

#include "Types.hpp"
#include "Compressor.hpp"
#include "Container.hpp"

static const constexpr FloatingType CompressorCylinders = 4;
static const constexpr FloatingType CompressorBoreMm = 55;
static const constexpr FloatingType CompressorStrokeMm = 39.3;
static const constexpr Volume CompressorVolume = CompressorCylinders * ((3.14f * (CompressorBoreMm*CompressorBoreMm) * CompressorStrokeMm) * 0.000000001);

static const constexpr Enthalpy InitialDischargeEnthalpy = 260;
static const constexpr Pressure InitialDischargePressure = 6;

static const constexpr Enthalpy InitialSuctionEnthalpy = 400;
static const constexpr Pressure InitialSuctionPressure = 4;

template <auto LengthCm, auto DiameterCm>
static constexpr auto PipeVolume()
{
    auto radius = static_cast<FloatingType>(DiameterCm)/2.f;
    return LengthCm * (3.14f * (radius * radius));
}

int main()
{    
    Container suction(PipeVolume<100, 10>(), 30000);
    Container discharge(PipeVolume<100, 10>(), 70000);
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
        std::cout << "PSuc\t" << std::to_string(suction.GetFluid().GetPressure()) << std::endl;
        std::cout << "HSuc\t" << std::to_string(suction.GetFluid().GetEnthalpy()) << std::endl;
        std::cout << "PDis\t" << std::to_string(discharge.GetFluid().GetPressure()) << std::endl;
        std::cout << "HDis\t" << std::to_string(discharge.GetFluid().GetEnthalpy()) << std::endl;
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
