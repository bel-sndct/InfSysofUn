#ifndef DEANERY_H
#define DEANERY_H
#include "human.h"

class Deanery : public Human
{
private:
    QString faculty;
    QString office;
    short build;
public:
    Deanery();
    Deanery(Deanery&);
    ~Deanery();
    inline QString getFaculty() { return faculty; }
    inline QString getOffice() { return office; }
    inline short getBuild() { return build; }
    void setFaculty(QString faculty);
    void setOffice(QString office);
    void setBuild(short build);
};


#endif // DEANERY_H
