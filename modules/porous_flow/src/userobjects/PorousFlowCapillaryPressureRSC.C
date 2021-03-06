/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "PorousFlowCapillaryPressureRSC.h"
#include "PorousFlowRogersStallybrassClements.h"

template <>
InputParameters
validParams<PorousFlowCapillaryPressureRSC>()
{
  InputParameters params = validParams<PorousFlowCapillaryPressure>();
  params.addParam<Real>("oil_viscosity",
                        "Viscosity of oil (gas) phase.  It is assumed this is "
                        "double the water-phase viscosity.  (Note that this "
                        "effective saturation is mostly useful for 2-phase, not "
                        "single-phase.)");
  params.addParam<Real>("scale_ratio",
                        "This is porosity / permeability / beta^2, where beta may "
                        "be chosen by the user.  It has dimensions [time]");
  params.addParam<Real>("shift", "effective saturation is a function of (Pc - shift)");
  params.addClassDescription("Rogers-Stallybrass-Clements version of effective saturation for the "
                             "water phase, valid for residual saturations = 0, and viscosityOil = "
                             "2 * viscosityWater.  seff_water = 1 / sqrt(1 + exp((Pc - shift) / "
                             "scale)), where scale = 0.25 * scale_ratio * oil_viscosity.");
  return params;
}

PorousFlowCapillaryPressureRSC::PorousFlowCapillaryPressureRSC(const InputParameters & parameters)
  : PorousFlowCapillaryPressure(parameters),
    _oil_viscosity(getParam<Real>("oil_viscosity")),
    _scale_ratio(getParam<Real>("scale_ratio")),
    _shift(getParam<Real>("shift")),
    _scale(0.25 * _scale_ratio * _oil_viscosity)
{
  // Set _log_ext to false as no capillary pressure curves are implmented in this class
  _log_ext = false;
}

Real PorousFlowCapillaryPressureRSC::capillaryPressureCurve(Real /*saturation*/) const
{
  mooseError("PorousFlowCapillaryPressureRSC::capillaryPressure not implemented");
  return 0.0;
}

Real PorousFlowCapillaryPressureRSC::dCapillaryPressureCurve(Real /*saturation*/) const
{
  mooseError("PorousFlowCapillaryPressureRSC::dCapillaryPressure not implemented");
  return 0.0;
}

Real PorousFlowCapillaryPressureRSC::d2CapillaryPressureCurve(Real /*saturation*/) const
{
  mooseError("PorousFlowCapillaryPressureRSC::d2CapillaryPressure not implemented");
  return 0.0;
}

Real
PorousFlowCapillaryPressureRSC::effectiveSaturation(Real pc) const
{
  return PorousFlowRogersStallybrassClements::effectiveSaturation(-pc, _shift, _scale);
}

Real
PorousFlowCapillaryPressureRSC::dEffectiveSaturation(Real pc) const
{
  return -PorousFlowRogersStallybrassClements::dEffectiveSaturation(-pc, _shift, _scale);
}

Real
PorousFlowCapillaryPressureRSC::d2EffectiveSaturation(Real pc) const
{
  return PorousFlowRogersStallybrassClements::d2EffectiveSaturation(-pc, _shift, _scale);
}
