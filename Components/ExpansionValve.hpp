#pragma once

#include <Types/Mass.hpp>
#include <Types/Percent.hpp>
#include <Helpers/Limit.hpp>

template <typename PortA, typename PortB>
class ExpansionValve
{
public:
  using FluidCalculator = typename PortA::Fluid::Calculator;

  ExpansionValve(Mass minFlow, Mass maxFlow, PortA& a, PortB& b) :
    _minFlow(minFlow),
    _maxFlow(maxFlow),
    _a(a),
    _b(b)
  {}

  void SetSignal(Percent signal)
  {
    _signal = signal;
  }

  auto Service(Seconds tick)
  {
    return Displace(tick);
  }

private:
  Mass _minFlow;
  Mass _maxFlow;
  Percent _signal;
  PortA& _a;
  PortB& _b;

  auto GetFlow() const
  {
      auto flowPrHour = Map<Rpm>(_signal, PercentMin, PercentMax, _minFlow.GetKg(), _maxFlow.GetKg());

      if (_signal == 0)
      {
        flowPrHour = 0;
      }

      return Mass::FromKg(flowPrHour / 3600);
  }

  void Displace(Seconds tick)
  {
    auto maxFlow = Mass::FromKg(GetFlow().GetKg() * tick);
    auto diff = _a.GetFluid().GetPressure().GetBar() - _b.GetFluid().GetPressure().GetBar();
    diff = Limit(diff, maxFlow.GetKg() / -1, maxFlow.GetKg());

    if (diff > 0)
    {
        auto actualFlow = _a.Out(diff);
        _b.In(actualFlow);
    }
    else
    {
        diff /= -1;
        auto actualFlow = _b.Out(diff);
        _a.In(actualFlow);
    }
  }
};
