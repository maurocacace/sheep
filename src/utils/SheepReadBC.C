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

#include "SheepReadBC.h"
#include "MooseError.h"

int SheepReadBC::_file_number = 0;

SheepReadBC::SheepReadBC(int nx,
                         int ny,
                         bool neumann,
                         const std::vector<double> & x,
                         const std::vector<std::string> & y,
                         const ColumnMajorMatrix & px,
                         const ColumnMajorMatrix & py,
                         const ColumnMajorMatrix & pv) :
    _nx(nx),
    _ny(ny),
    _has_neumann(neumann),
    _x(x),
    _y(y),
    _px(px),
    _py(py),
    _pv(pv)
{
    errorCheck();
}

void
SheepReadBC::errorCheck()
{
    if (_x.size() != _y.size())
        mooseError("In SheepReadBC: Vectors _x & _y are not of the same length");
    bool error = false;
    for (unsigned i = 0; !error && i + 1 < _x.size(); ++i)
    {
        if (_x[i] >= _x[i+1])
            error = true;
    }
    if (error)
        mooseError( "In SheepReadBC: x-values are not strictly increasing" );
}

double
SheepReadBC::sample(double t, double xcoord, double ycoord)
{
    mooseAssert(_x.size() > 0, "Sampling an empty SheepReadBC.");
    int posi;
    int posj;

    if(_y.size()>1)
    {
        for(unsigned int i(0); i <_y.size() - 1; ++i)
        {
            if(t <= _x[0])
            {
                posi = 0;
                break;
            }
            else if(t >= _x.back())
            {
                posi = _x.size()-1;
                break;
            }
            else if(t >= _x[i] && t < _x[i+1])
            {
                posi = i;
                break;
            }
        }
    }
    else
    {
        if(t != _x[0])
        {
            mooseError("In SheepReadBC::sample : t= "<<t<<" but _x= "<<_x[0]);
        }
        posi = 0;
    }
    if(!_has_neumann)
    {
        for(unsigned int i(0); i < _nx * _ny; ++i)
        {
            if( (std::fabs(_px(posi, i) - xcoord) < 0.1) && (std::fabs(_py(posi, i)- ycoord) < 0.1) )
            {
                return _pv(posi, i);
            }
        }
        mooseError("Unreachable? Dirichlet: x="<<xcoord<<" , y="<<ycoord<<" , file="<<_y[posi]<<" !!" );
    }
    else
    {
        double value = 0.0;
        int count = 0;
        for(unsigned int i(0); i < _ny - 1; ++i)
            for(unsigned int j(0); j < _nx - 1; ++j)
                if( (_px(posi,(i * _nx) + j) < xcoord && _px(posi,(i * _nx) + j + 1) > xcoord) &&
                    (_py(posi,(i * _nx) + j) < ycoord && _py(posi,(i + 1)*_nx + j) > ycoord))
                {
                    value += _pv(posi, (i * _nx) + j) + _pv(posi, (i * _nx) + j + 1) + _pv(posi, (i + 1) * _nx + j) + _pv(posi, (i + 1) * _nx + j + 1);
                    value /= 4;
                    count++;
                }
        if(count > 0)
            value /= count;
        else if (count == 0)
            mooseError("Unreachable? Neumann: x="<<xcoord<<" , y="<<ycoord<<" , file="<<_y[posi]<< count <<" !!" );
        return value;
    }
    return 0;
}

double
SheepReadBC::sampleTime(double t, double xcoord, double ycoord)
{

    mooseAssert(_x.size() > 0, "Sampling an empty SheepReadBC.");
    int posi;
    int posj;
    bool found = false;
    if(t <= _x[0])
    {
        posi = 0;
        for(unsigned int i(0); i < _nx * _ny; ++i)
            if( (std::fabs(_px(posi, i) - xcoord) < 0.1) && (std::fabs(_py(posi, i)- ycoord) < 0.1) )
                return _pv(posi, i);
        mooseError("Unreachable? Dirichlet: x="<<xcoord<<" , y="<<ycoord<<" , file="<<_y[posi]<<" !!" );
    }
    else if(t >= _x.back())
    {
        posi = _x.size()-1;
        for(unsigned int i(0); i < _nx * _ny; ++i)
            if( (std::fabs(_px(posi, i) - xcoord) < 0.1) && (std::fabs(_py(posi, i)- ycoord) < 0.1) )
                return _pv(posi, i);
        mooseError("Unreachable? Dirichlet: x="<<xcoord<<" , y="<<ycoord<<" , file="<<_y[posi]<<" !!" );
    }
    else
    {
        found = false;
        for(unsigned int i(0); i+1 < _x.size(); ++i)
        {
            if( t >= _x[i] && t < _x[i+1])
            {
                posi = i;
                found = true;
                break;
            }
        }
        if( !found )
            mooseError("Unreachable? sampleTime: x="<<xcoord<<" , y="<<ycoord<<" , posi="<<posi<<" !!" );

        found = false;
        for(unsigned int j(0); j < _nx* _ny; ++j)
        {
            if(std::fabs(_px(posi, j) - xcoord) < 0.1 && std::fabs(_py(posi, j) - ycoord) < 0.1)
            {
                posj = j;
                found = true;
                break;
            }
        }
        if( !found )
            mooseError("Unreachable? sampleTime: x="<<xcoord<<" , y="<<ycoord<<" , posj="<<posj<<" !!" );
        return _pv(posi,posj) + (_pv(posi+1,posj) - _pv(posi,posj)) * (t - _x[posi])/(_x[posi+1] - _x[posi]);
    }
    return 0;
}

double
SheepReadBC::sampleDerivative(double t, double xcoord, double ycoord)
{
    int posi;
    int posj;
    mooseAssert(_x.size() > 0, "Sampling an empty SheepReadBC.");
    if(t <= _x[0])
        return 0.0;
    if(t >= _x[_x.size()-1])
        return 0.0;
    for(unsigned int i(0); i+1 < _x.size(); ++i)
    {
        if( t >= _x[i] && t < _x[i+1])
        {
            posi = i;
            break;
        }
    }
    if(posi + 1 == _x.size())
        mooseError("Unreachable? sampleDerivative: x="<<xcoord<<" , y="<<ycoord<<" , posi="<<posi<<" !!" );
    for(unsigned int j(0); j < _nx* _ny; ++j)
    {
        if(std::fabs(_px(posi, j) - xcoord) < 0.1 && std::fabs(_py(posi, j) - ycoord) < 0.1)
        {
            posj = j;
            break;
        }
    }
    if(posj + 1 == (_nx*_ny))
        mooseError("Unreachable? sampleDerivative: x="<<xcoord<<" , y="<<ycoord<<" , posj="<<posj<<" !!" );
    return ( _pv(posi + 1,posj) - _pv(posi,posj) ) / ( _x[posi+1] - _x[posi] );
}

double
SheepReadBC::integrate(double xcoord, double ycoord)
{
    double answer(0);
    int posi;
    for(unsigned int i(0); i < _nx* _ny; ++i)
    {
        if(std::fabs(_px(0, i) - xcoord) < 0.1 && std::fabs(_py(0, i) - ycoord) < 0.1)
        {
            posi = i;
            break;
        }
    }
    for(unsigned int i(1); i < _x.size(); ++i)
        answer += 0.5*(_pv(i, posi) + _pv(i-1, posi))*(_x[i] - _x[i-1]);
    return answer;
}
