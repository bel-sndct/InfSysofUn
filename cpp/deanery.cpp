#include "deanery.h"

Deanery::Deanery() : Human()
{
    faculty = "";
    office = "";
    build = 0;
}

Deanery::Deanery(Deanery& deanery) : Human(deanery)
{
    faculty = deanery.faculty;
    office = deanery.office;
    build = deanery.build;
}

Deanery::~Deanery()
{
    faculty.~QString();
    office.~QString();
}

void Deanery::setFaculty(QString faculty)
{
    this->faculty = faculty;
}

void Deanery::setOffice(QString office)
{
    this->office = office;
}

void Deanery::setBuild(short build)
{
    this->build = build;
}
