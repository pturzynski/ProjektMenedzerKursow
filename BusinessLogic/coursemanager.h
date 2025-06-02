#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H
#include "course.h"
#include "user.h"
#include <QList>
#include <QString>
#include "BusinessLogic_global.h"

class BUSINESSLOGIC_EXPORT CourseManager
{
private:
    QList<Course> allCourses; //lista wszystkich kursow
    QList<Course> studentCourses; //lista kursow studenta
    int nextId = 1;

public:
    CourseManager();

    //gettery
    QList<Course> getAllCourses() const;
    QList<Course> getStudentCourses() const;

    //metody zapisywania i wczytywania z pliku
    void loadAllCourses();
    void saveAllCourses();
    void saveStudentCourses();
    void loadStudentCourses();
    bool enrollStudent(int courseId);

    //metody dla admina
    bool addCourse(const User* user, const QString& name, const QString& description);
    bool removeCourse(const User* user, int courseId);
    bool removeCourseCompletely(int courseId);

};

#endif // COURSEMANAGER_H
