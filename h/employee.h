#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "human.h"

class Employee : public Human
{
protected:
    long id_number;
    bool debt;
    QString speciality;
    long group_number;
    int course;
    double average_score;
public:
    Employee();
    Employee(Employee&);
    ~Employee();
    inline long getId() const {return id_number;}
    inline bool getDebt(){return debt;}
    inline long getGroupNumber() const {return group_number;}
    inline QString getSpeciality(){return speciality;}
    inline int getCourse(){return course;}
    inline double getAverageScore(){return average_score;}
    void setId(long id_number);
    void setDebt(bool debt);
    void setGroupNumber(long group_number);
    void setCourse(int course);
    void setSpeciality(QString speciality);
    void setAverageScore(double average_score);
};


#endif // EMPLOYEE_H
