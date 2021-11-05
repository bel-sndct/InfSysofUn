#ifndef HUMAN_H
#define HUMAN_H
#include<QString>

class Human
{
protected:
    QString l_name;
    QString f_name;
    QString m_name;
    QString email;
    long long tel_number;
public:
    Human(QString l_name, QString f_name, QString m_name, QString email, long long tel_number);
    Human();
    Human(Human&);
    ~Human();
    inline QString getLName() const {return l_name;}
    inline QString getFName() const {return f_name;}
    inline QString getMName() const{return m_name;}
    inline QString getEmail(){return email;}
    inline long long getTelNumber(){return tel_number;}
    void setLName(QString l_name);
    void setFName(QString f_name);
    void setMName(QString m_name);
    void setEmail(QString email);
    void setTelNumber(long long tel_number);
};

#endif // HUMAN_H
