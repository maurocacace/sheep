/****************************************************************/
/*             DO NOT MODIFY OR REMOVE THIS HEADER              */
/*          FALCON - Fracturing And Liquid CONvection           */
/*                                                              */
/*       (c)     2012 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "THDarcyFluxAux.h"

template<>
InputParameters validParams<THDarcyFluxAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<int>("component", 0, "component of the Darcy flux vector");
  return params;
}

THDarcyFluxAux::THDarcyFluxAux(const InputParameters & parameters):
    AuxKernel(parameters),
    _wdflx(getMaterialProperty<RealGradient>("darcy_flux_water")),
    _i(getParam<int>("component"))
{}

Real
THDarcyFluxAux::computeValue()
{
    return _wdflx[_qp](_i);
}


