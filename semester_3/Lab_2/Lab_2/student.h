#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{

public:
    QString name = "";
    QString group = "";
    QString organization = "";
    QString contact = "";

    Student(QString _name = "", QString _group = "", QString _org = "", QString _contact = "");
    QString getInfo();
};

#endif // STUDENT_H
