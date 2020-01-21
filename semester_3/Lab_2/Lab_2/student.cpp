#include "student.h"

Student::Student(QString _name, QString _group, QString _org, QString _contact)
{
    name = _name;
    group = _group;
    organization = _org;
    contact = _contact;
}

QString Student::getInfo(){
    QString studentInfo = name;
    studentInfo += ", ";
    studentInfo += group;
    studentInfo += ", ";
    studentInfo += organization;
    return studentInfo;
}
