#include "employee.h"

Employee::Employee() : Human()
{
    id_number = 0;
    group_number = 0;
    speciality = "";
    course = 1;
    debt = false;
    average_score = 0;
}

Employee::Employee(Employee &employee) : Human(employee)
{
    id_number = employee.id_number;
    group_number = employee.group_number;
    course = employee.course;
    debt = employee.debt;
    speciality = employee.speciality;
    average_score = employee.average_score;
}

Employee::~Employee()
{
    speciality.~QString();
}

void Employee::setId(long id_number)
{
    this->id_number = id_number;
}

void Employee::setDebt(bool debt)
{
    this->debt = debt;
}

void Employee::setGroupNumber(long group_number)
{
    this->group_number = group_number;
}

void Employee::setSpeciality(QString name_spec)
{
    this->speciality = name_spec;
}

void Employee::setAverageScore(double average_score)
{
    this->average_score = average_score;
}

void Employee::setCourse(int course)
{
    this->course = course;
}











