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

#ifndef THDARCYFLUXAUX_H
#define THDARCYFLUXAUX_H

#include "AuxKernel.h"

class THDarcyFluxAux;

template<>
InputParameters validParams<THDarcyFluxAux>();

class THDarcyFluxAux : public AuxKernel
{
public:
    THDarcyFluxAux(const InputParameters & parameters);
    virtual ~THDarcyFluxAux() {}
protected:
    virtual Real computeValue();
    const MaterialProperty<RealGradient> & _wdflx;
    int _i;
};
#endif //THDARCYFLUXAUX_H
