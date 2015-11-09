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

#ifndef THFLUIDVELOCITYAUX_H
#define THFLUIDVELOCITYAUX_H

#include "THDarcyFluxAux.h"

class THFluidVelocityAux;

template<>
InputParameters validParams<THFluidVelocityAux>();

class THFluidVelocityAux : public THDarcyFluxAux
{
public:
    THFluidVelocityAux(const InputParameters & parameters);
    virtual ~THFluidVelocityAux() {}
protected:
    virtual Real computeValue();
    const MaterialProperty<Real> & _poro;
};
#endif //THFLUIDVELOCITYAUX_H
