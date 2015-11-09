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
#ifndef SHEEPREADBC_H
#define SHEEPREADBC_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "ColumnMajorMatrix.h"

class SheepReadBC
{
public:
    SheepReadBC(int nx,
                int ny,
                bool neumann,
                const std::vector<double> & x,
                const std::vector<std::string> & y,
                const ColumnMajorMatrix & px,
                const ColumnMajorMatrix & py,
                const ColumnMajorMatrix & pv);
    SheepReadBC() :
        _nx(0),
        _ny(0),
        _has_neumann(false),
        _x(std::vector<double>()),
        _y(std::vector<std::string>()){}
    virtual ~SheepReadBC(){}
    void errorCheck();
    double sample(double t, double xcoord, double ycoord );
    double sampleTime(double t, double xcoord, double ycoord );
    double sampleDerivative(double t, double xcoord, double ycoord);
    double integrate(double xcoord, double ycoord);
private:
    int _nx;
    int _ny;
    bool _has_neumann;
    const std::vector<double> _x;
    const std::vector<std::string> _y;
    ColumnMajorMatrix _px;
    ColumnMajorMatrix _py;
    ColumnMajorMatrix _pv;
    static int _file_number;
};
#endif // SHEEPREADBC_H

