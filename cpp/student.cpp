#include "student.h"
#include <cmath>

Student::Student() : Employee()
{
    entrance_year = 2020;
}

Student::Student(Student &student) : Employee(student)
{
    entrance_year = student.entrance_year;
}

Student::~Student()
{
    entrance_year = 0;
}

void Student::setEntranceYear(int entrance_year)
{
    this->entrance_year = entrance_year;
}
