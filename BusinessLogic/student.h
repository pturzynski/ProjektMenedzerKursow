#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"
class BUSINESSLOGIC_EXPORT Student : public User
{
public:
    Student(const QString &username, const QString &password);
    bool isAdmin() const override { return false; }
};

#endif // STUDENT_H
