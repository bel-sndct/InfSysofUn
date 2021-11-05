#ifndef UNDERGRADUATE_H
#define UNDERGRADUATE_H

#include "employee.h"

class Undergraduate : public Employee
{
private:
    int entrance_year;
    QString res_work;
public:
    Undergraduate();
    Undergraduate(Undergraduate&);
    ~Undergraduate();
    inline QString getResWork() { return res_work; }
    inline int getEntranceYear() {return entrance_year;}
    void setResWork(QString res_work);
    void setEntranceYear(int entrance_year);
};

#endif // UNDERGRADUATE_H
