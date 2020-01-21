#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student(QString _name = "", QString _group = "", QString _org = "", QString _contact = "");
    QString name = "";
    QString group = "";
    QString organization = "";
    QString contact = "";
};

#endif // STUDENT_H
