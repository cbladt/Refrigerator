#include <string>

#include <CoolProp.h>

#include <Types/Temperature.hpp>
#include <Types/Pressure.hpp>
#include <Types/Enthalpy.hpp>
#include <Types/Density.hpp>
#include <Types/Enthropy.hpp>

template <unsigned Fluid>
class FluidCalculator
{
public:
    static Temperature TemperatureFromPressureAndEnthalpy(Pressure pressure, Enthalpy enthalpy)
    {
        return Temperature::FromKelvin(CoolProp::PropsSI("T", "P", pressure.GetPascal(), "H", enthalpy.GetJPrKg(), FluidCalculator::GetFluid()));
    }

    static Density GasDensityFromPressureAndTemperature(Pressure pressure, Temperature temperature)
    {
        return Density::FromKgM3(CoolProp::PropsSI("D", "T|gas", temperature.GetKelvin(), "P", pressure.GetPascal(), FluidCalculator::GetFluid()));
    }

    static Enthropy EnthropyFromEnthalpyAndPressure(Enthalpy enthalpy, Pressure pressure)
    {
       return Enthropy::FromJPrKgPrK(CoolProp::PropsSI("S", "H", enthalpy.GetJPrKg(), "P", pressure.GetPascal(), FluidCalculator::GetFluid()));
    }

    static Enthalpy EnthalpyFromPressureAndEnthropy(Pressure pressure, Enthropy enthropy)
    {
        return Enthalpy::FromJPrKg(CoolProp::PropsSI("H", "P", pressure.GetPascal(), "S", enthropy.GetJPrKgPrK(), FluidCalculator::GetFluid()));
    }

private:
    static std::string GetFluid()
    {
        switch (Fluid)
        {
            case 1341: return "HEOS::R134A";
            default: return "HEOS::R134A";
        }
    }
};
