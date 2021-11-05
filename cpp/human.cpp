#include "human.h"

Human::Human(QString l_name, QString f_name, QString m_name,QString email, long long tel_number)
{
    this->l_name = l_name;
    this->f_name = f_name;
    this->m_name = m_name;
    this->email = email;
    this->tel_number = tel_number;
}
Human::Human()
{
    l_name = "";
    f_name = "";
    m_name = "";
    email = "";
    tel_number = 0;
}
Human::Human(Human &human)
{
    l_name = human.l_name;
    f_name = human.f_name;
    m_name = human.m_name;
    email = human.email;
    tel_number = human.tel_number;
}
Human::~Human()
{
    l_name.~QString();
    f_name.~QString();
    m_name.~QString();
    email.~QString();
}
void Human::setLName(QString l_name)
{
    this->l_name = l_name;
}
void Human::setFName(QString f_name)
{
    this->f_name = f_name;
}
void Human::setMName(QString m_name)
{
    this->m_name = m_name;
}
void Human::setEmail(QString email)
{
    this->email = email;
}
void Human::setTelNumber(long long tel_number)
{
    this->tel_number = tel_number;
}
