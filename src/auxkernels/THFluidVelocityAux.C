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

#include "THFluidVelocityAux.h"

template<>
InputParameters validParams<THFluidVelocityAux>()
{
    InputParameters params = validParams<THDarcyFluxAux>();
    return params;
}

THFluidVelocityAux::THFluidVelocityAux(const InputParameters & parameters):
    THDarcyFluxAux(parameters),
    _poro(getMaterialProperty<Real>("porosity"))
{
}


Real
THFluidVelocityAux::computeValue()
{
    return THDarcyFluxAux::computeValue() / _poro[_qp];
}

