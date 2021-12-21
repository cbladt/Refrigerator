#pragma once

#include <Types/Mass.hpp>
#include <Types/Percent.hpp>
#include <Helpers/Limit.hpp>

template <typename PortA, typename PortB>
class ExpansionValve
{
public:
  using FluidCalculator = typename PortA::Fluid::Calculator;

  ExpansionValve(PortA& a, PortB& b) :
    _a(a),
    _b(b)
  {}

  auto Service(Seconds tick)
  {
    return Displace(tick);
  }

private:
  PortA& _a;
  PortB& _b;

  void Displace(Seconds tick)
  {
    _a.GetFluid().AddEnthalpy(Enthalpy::FromKjPrKg(1));
  }
};
