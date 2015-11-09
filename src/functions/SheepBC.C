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

#include "SheepBC.h"

template<>
InputParameters validParams<SheepBC>()
{
    InputParameters params = validParams<Function>();
    params.addParam<std::string>("data_file", "File holding csv/tab-separated bc data.");
    params.addParam<std::string>("format", "rows" ,"Format of csv data file that is in either in columns or rows.");
    params.addParam<int>("nx", 0, "the number of x points.");
    params.addParam<int>("ny", 0, "the number of y points.");
    params.addParam<bool>("neumann", false, "Is a neumann bc?");
    params.addParam<bool>("interpol", false, "linearly interpolating among the data in time");
    return params;
}

SheepBC::SheepBC(const InputParameters & parameters) :
    Function(parameters),
    _sheep_read_bc(NULL),
    _nx(getParam<int>("nx")),
    _ny(getParam<int>("ny")),
    _has_file(false),
    _has_neumann(getParam<bool>("neumann")),
    _has_interpol(getParam<bool>("interpol")),
    _data_file_name(isParamValid("data_file") ? getParam<std::string>("data_file") : "")
{
    std::vector<Real> x;
    std::vector<std::string> y;
    std::string format = getParam<std::string>("format");
    if(format.compare(0,4,"file")==0)
    {
        if(_data_file_name != "")
        {
            parseFile(x,y);
            _has_file = true;
        }
        else
            mooseError("In SheepBC: data_file_name is not specified.");
    }else
        mooseError("In SheepBC: format must be specified.");
    if(_has_file)
    {
        ColumnMajorMatrix px(x.size(), _nx*_ny);
        ColumnMajorMatrix py(x.size(), _nx*_ny);
        ColumnMajorMatrix pz(x.size(), _nx*_ny);
        fillMatrixBC(px, py, pz, x, y);
        _sheep_read_bc = new SheepReadBC(_nx, _ny, _has_neumann, x, y, px, py, pz);
    }
}

SheepBC::~SheepBC()
{
    delete _sheep_read_bc;
}

bool
SheepBC::parseNextLineReals(std::ifstream & ifs, std::vector<Real> & myvec)
{
    std::string line;
    myvec.clear();
    bool gotline(false);
    if(getline(ifs, line))
    {
        gotline = true;
        while(size_t pos=line.find(','))
        {
            if(pos==line.npos)
                break;
            line.replace(pos, 1, 1, ' ');
        }
        std::istringstream iss(line);
        Real f;
        while(iss>>f)
            myvec.push_back(f);
    }
    return gotline;
}

bool
SheepBC::parseNextLineStrings(std::ifstream & ifs, std::vector<std::string> & myvec)
{
    std::string line;
    myvec.clear();
    bool gotline(false);
    if(getline(ifs, line))
    {
        gotline = true;
        while(size_t pos=line.find(','))
        {
            if(pos==line.npos)
                break;
            line.replace(pos, 1, 1, ' ');
        }
        std::istringstream iss(line);
        std::string s;
        while(iss>>s)
            myvec.push_back(s);
    }
    return gotline;
}

void
SheepBC::parseFile( std::vector<Real> & x, std::vector<std::string> & y )
{
    std::ifstream file(_data_file_name.c_str());
    if(!file.good())
        mooseError("Error opening file '"+_data_file_name+"' from SheepBC function.");
    std::string line;
    while(parseNextLineReals(file, x))
    {
        if(x.size()>0)
            break;
    }
    if(x.size() == 0)
        mooseError("File '"+_data_file_name+"' contains no data for SheepBC function.");
    while(parseNextLineStrings(file, y))
    {
        if(y.size()>0)
            break;
    }
    if(y.size() == 0)
        mooseError("File '"+_data_file_name+"' contains no y data for SheepBC function.");
    else if(y.size() != x.size())
        mooseError("Lengths of x and y data do not match in file '" + _data_file_name + "' for SheepBC function.");
    std::vector<Real> scratch;
    while (parseNextLineReals(file, scratch)){
        if (scratch.size() > 0)
            mooseError("Read more than two rows of data from file '" + _data_file_name + "' for SheepBC function.");
    }
}

void
SheepBC::fillMatrixBC(ColumnMajorMatrix & px, ColumnMajorMatrix & py, ColumnMajorMatrix & pz, std::vector<double> & x, std::vector<std::string> & y)
{
    std::string line;
    std::vector<double> scratch;
    px.reshape(x.size(), _nx*_ny);
    py.reshape(x.size(), _nx*_ny);
    pz.reshape(x.size(), _nx*_ny);
    std::vector<double> myx;
    std::vector<double> myy;
    std::vector<double> myv;
    for(unsigned int i(0); i < x.size(); ++i)
    {
        std::ifstream file(y[i].c_str());
        if (!file.good())
            mooseError("Error opening file '" + y[i] + "' from SheepBC function.");

        while (parseNextLineReals(file, scratch))
        {
            if (scratch.size() > 0){
                if (scratch.size() != 3)
                    mooseError("Read more than 3 columns of data from file '" + y[i] + "' in SheepBC function.");
                myx.push_back(scratch[0]);
                myy.push_back(scratch[1]);
                myv.push_back(scratch[2]);
            }
        }
        for(unsigned int j(0); j < myx.size(); ++j)
        {
            px(i,j) = myx[j];
            py(i,j) = myy[j];
            pz(i,j) = myv[j];
        }
        myx.clear();
        myy.clear();
        myv.clear();
    }
}



