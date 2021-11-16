#include <iostream>

#include "Types.hpp"
#include "Compressor.hpp"
#include "Container.hpp"

static const constexpr FloatingType CompressorCylinders = 4;
static const constexpr FloatingType CompressorBoreMm = 55;
static const constexpr FloatingType CompressorStrokeMm = 39.3;
static const constexpr VolumeM3 CompressorVolume = CompressorCylinders * ((3.14f * (CompressorBoreMm*CompressorBoreMm) * CompressorStrokeMm) * 0.000000001);

static const constexpr Kelvin InitialDischargeTemperature = 273.15f + 40.f;
static const constexpr BarAbsolute InitialDischargePressure = 6;
static const constexpr Kelvin InitialSuctionTemperature = 273.15f + 5.f;
static const constexpr BarAbsolute InitialSuctionPressure = 4;

template <auto LengthCm, auto DiameterCm>
static constexpr auto PipeVolume()
{
    auto radius = static_cast<FloatingType>(DiameterCm)/2.f;
    return LengthCm * (3.14f * (radius * radius));
}

int main()
{    
    Container suction(PipeVolume<30, 1>());
    Container discharge(PipeVolume<30, 1>());
    Container afterCondensor(PipeVolume<30, 1>());
    Container beforeEvaporator(PipeVolume<10, 1>());

    Compressor compressor(1000, 3000, CompressorVolume, suction, discharge);

    suction.GetFluid().SetTemperature(InitialSuctionTemperature);
    suction.GetFluid().SetPressure(InitialSuctionPressure);

    afterCondensor.GetFluid().SetTemperature(InitialSuctionTemperature);
    afterCondensor.GetFluid().SetPressure(InitialSuctionPressure);

    discharge.GetFluid().SetTemperature(InitialDischargeTemperature);
    discharge.GetFluid().SetPressure(InitialDischargePressure);

    afterCondensor.GetFluid().SetTemperature(InitialDischargeTemperature);
    afterCondensor.GetFluid().SetPressure(InitialDischargePressure);


    return 0;
}
