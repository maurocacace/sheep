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

#ifndef SHEEPBC_H
#define SHEEPBC_H

#include "Function.h"
#include "SheepReadBC.h"

#include "ColumnMajorMatrix.h"

/**
 * Base class for function objects. Functions override value to supply a
 * value at a point
 */

class SheepBC : public Function
{
public:
    SheepBC(const InputParameters & parameters);
    virtual ~SheepBC();
protected:
    SheepReadBC * _sheep_read_bc;
    int _nx;
    int _ny;
    bool _has_file;
    bool _has_neumann;
    bool _has_interpol;
private:
    const std::string _data_file_name;
    bool parseNextLineReals(std::ifstream & ifs, std::vector<Real> & myvec);
    bool parseNextLineStrings(std::ifstream & ifs, std::vector<std::string> & myvec);
    void parseFile(std::vector<Real> & x, std::vector<std::string> & y);
    void fillMatrixBC(ColumnMajorMatrix & px, ColumnMajorMatrix & py, ColumnMajorMatrix & pz, std::vector<double> & x, std::vector<std::string> & y);
};

template<>
InputParameters validParams<SheepBC>();

#endif // SHEEPBC
