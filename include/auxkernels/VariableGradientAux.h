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

#ifndef VARIABLEGRADIENTAUX_H
#define VARIABLEGRADIENTAUX_H

#include "AuxKernel.h"

class VariableGradientAux;

template<>
InputParameters validParams<VariableGradientAux>();

class VariableGradientAux : public AuxKernel
{
public:
    /**
     * Factory constructor, takes parameters so that all
     * derived classes can be built using the same
     * constructor.
     */
    VariableGradientAux(const InputParameters & parameters);
    virtual ~VariableGradientAux() {}
  protected:
    virtual Real computeValue();
    VariableGradient & _grad_coupled_variable;
    int _i;
};

#endif //VARIABLEGRADIENTAUX_H
