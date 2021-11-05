#include "undergraduate.h"
#include <cmath>

Undergraduate::Undergraduate() : Employee()
{
    res_work = "";
    entrance_year = 0;
}

Undergraduate::Undergraduate(Undergraduate& undergraduate) : Employee(undergraduate)
{
    res_work = undergraduate.res_work;
    entrance_year = undergraduate.entrance_year;
}

Undergraduate::~Undergraduate()
{
    res_work.~QString();
}

void Undergraduate::setResWork(QString res_work)
{
    this->res_work = res_work;
}

void Undergraduate::setEntranceYear(int entrance_year)
{
    this->entrance_year = entrance_year;
}









