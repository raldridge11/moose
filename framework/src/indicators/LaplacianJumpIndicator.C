/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "LaplacianJumpIndicator.h"

template <>
InputParameters
validParams<LaplacianJumpIndicator>()
{
  InputParameters params = validParams<InternalSideIndicator>();
  return params;
}

LaplacianJumpIndicator::LaplacianJumpIndicator(const InputParameters & parameters)
  : InternalSideIndicator(parameters), _second_u(second()), _second_u_neighbor(neighborSecond())
{
}

Real
LaplacianJumpIndicator::computeQpIntegral()
{
  Real jump = (_second_u[_qp].tr() - _second_u_neighbor[_qp].tr());

  return jump * jump;
}
