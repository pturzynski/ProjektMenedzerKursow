#include "course.h"
#include "exceptions.h"

Course::Course(int id, const QString &name, const QString &description)
    : id(id), name(name), description(description)
{
    if (name.isEmpty() || description.isEmpty()) {
        throw CourseEmptyException("Nazwa i opis nie mogą być puste");
    }
}

int Course::getId() const
{
    return id;
}

QString Course::getName() const
{
    return name;
}

QString Course::getDescription() const
{
    return description;
}
