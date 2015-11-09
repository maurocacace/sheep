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

#ifndef SHEEPFUNCTIONBC_H
#define SHEEPFUNCTIONBC_H

#include "SheepBC.h"

/**
 * Base class for function objects.  Functions override value to supply a
 * value at a point.
 */

class SheepFunctionBC : public SheepBC
{
public:
    SheepFunctionBC(const InputParameters & parameters);
    virtual ~SheepFunctionBC();
    virtual Real value(Real t, const Point & pt);
    virtual Real timeDerivative(Real t, const Point & pt);
    virtual Real integral(const Point & pt);
    virtual Real average();
};

template<>
InputParameters validParams<SheepFunctionBC>();

#endif //SHEEPFUNCTIONBC_H
