#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
public:
    Student(QString _name, QString _group, QString _org, int _id);
    QString name = "";
    QString group = "";
    QString organization = "";
    int id = -1;
};

#endif // STUDENT_H
