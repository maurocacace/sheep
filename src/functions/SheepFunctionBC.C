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

#include "SheepFunctionBC.h"

template<>
InputParameters validParams<SheepFunctionBC>()
{
    InputParameters params = validParams<SheepBC>();
    return params;
}

SheepFunctionBC::SheepFunctionBC(const InputParameters & parameters) :
    SheepBC(parameters)
{
}

SheepFunctionBC::~SheepFunctionBC()
{
}

Real
SheepFunctionBC::value(Real t, const Point & p)
{
    Real func_value;

    if( _has_file )
    {
        if(!_has_interpol)
        {
            func_value = _sheep_read_bc->sample(t, p(0), p(1));
        }
        else
        {
            func_value = _sheep_read_bc->sampleTime(t, p(0), p(1));
        }
    }
    return func_value;
}

Real
SheepFunctionBC::timeDerivative(Real t, const Point & p)
{
    return _sheep_read_bc->sampleDerivative(t, p(0), p(1));
}

Real
SheepFunctionBC::integral(const Point & p)
{
  return _sheep_read_bc->integrate(p(0), p(1));
}

Real
SheepFunctionBC::average()
{
  return 0.0;
}






