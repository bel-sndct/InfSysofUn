#ifndef STUDENT_H
#define STUDENT_H
#include "employee.h"


class Student : public Employee
{
private:
    int entrance_year;
public:
    Student();
    Student(Student&);
    ~Student();
    inline int getEntranceYear() {return entrance_year;}
    void setEntranceYear(int entrance_year);
};

#endif // STUDENT_H
