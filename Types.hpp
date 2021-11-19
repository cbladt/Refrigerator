#pragma once

#include "Helpers/Limit.hpp"

using FloatingType = double;

using Temperature = FloatingType;

using Pressure = FloatingType;
static const constexpr auto BarAbsoluteToPascal = 100000;

using Enthalpy = FloatingType;
static const constexpr auto EnthalpyKjPrKgToJPrKg = 1000;

using Density = FloatingType;

using Rpm = FloatingType;

using Volume = FloatingType;

using Mass = FloatingType;

using Percent = FloatingType;
static const constexpr auto PercentMin = 0;
static const constexpr auto PercentMax = 100;
