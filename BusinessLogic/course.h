#ifndef COURSE_H
#define COURSE_H
#include <QString>
#include "BusinessLogic_global.h"
using namespace std;
class BUSINESSLOGIC_EXPORT Course
{
private:
    QString name;
    QString description;
    int id;
public:
    Course(int id, const QString &name, const QString &description);

    int getId() const;
    QString getName() const;
    QString getDescription() const;
};

#endif // COURSE_H
