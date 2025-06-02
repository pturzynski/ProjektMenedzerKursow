#include "coursemanager.h"
#include "exceptions.h"
#include <QFile>
#include <QTextStream>

CourseManager::CourseManager() {
    loadAllCourses();

    QFile file("kursystudenta.txt");
    if (file.exists() && file.size() > 0) {
        loadStudentCourses();
    }
}

QList<Course> CourseManager::getAllCourses() const
{
    return allCourses;
}

QList<Course> CourseManager::getStudentCourses() const
{
    return studentCourses;
}

//zapisuje kursy STUDENTA do pliku txt
void CourseManager::saveStudentCourses()
{

    QFile file("kursystudenta.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw FileWriteException("kursystudenta.txt");
    }

    QTextStream out(&file);
    for (int i = 0; i < studentCourses.size(); ++i) {
        const Course& c = studentCourses[i];
        //format zapisu id;nazwa;opis
        out << c.getId() << ";" << c.getName() << ";" << c.getDescription() << "\n";
    }

    file.close();
}

//wczytuje kursy STUDENTA z pliku txt
void CourseManager::loadStudentCourses()
{
    QFile file("kursystudenta.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileOpenException("kursystudenta.txt");
    }

    QTextStream in(&file);
    studentCourses.clear();

    //odczytuje linie z pliku
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(';');
        if (parts.size() < 3)
            continue; // jesli jest wiecej nic 3 ; to pomijamy ta linijke bo jest niepoprawna

        bool czyok;
        int id = parts[0].toInt(&czyok); //part[0] wskazuje nam na ID kursu i konwertujemy na int, jesli jest string to wyrzuca blad
        if (!czyok) {
            throw FileReadException("Nieprawidłowy id kursu w pliku txt " + parts[0].toStdString());
        }

        QString name = parts[1];
        QString description = parts.mid(2).join(";");

        studentCourses.append(Course(id, name, description));
    }

    file.close();

    //usuwamy kurs na ktory sie zapisal student z listy wszytkich kursow
    for (int i = 0; i < studentCourses.size(); ++i) {
        int idToRemove = studentCourses[i].getId();

        for (auto j = allCourses.begin(); j != allCourses.end(); ) {
            if (j->getId() == idToRemove) {
                j = allCourses.erase(j);
            } else {
                ++j;
            }
        }
    }
}

bool CourseManager::enrollStudent(int courseId)
{
    for (int i = 0; i < allCourses.size(); ++i)
    {
        if (allCourses[i].getId() == courseId)
        {
            studentCourses.append(allCourses[i]);
            allCourses.removeAt(i);
            saveStudentCourses();
            return true;
        }
    }
    return false;
}

//klasa dla admina do dodawania kursow
bool CourseManager::addCourse(const User* user, const QString& name, const QString& description)
{
    if (!user->isAdmin())
        return false;

    allCourses.append(Course(nextId++, name, description));
    saveAllCourses();
    return true;
}

bool CourseManager::removeCourse(const User* user, int courseId)
{
    if (!user->isAdmin())
        return false;

    for (int i = 0; i < allCourses.size(); ++i)
    {
        if (allCourses[i].getId() == courseId)
        {
            allCourses.removeAt(i);
            saveAllCourses();
            return true;
        }
    }
    return false;
}

void CourseManager::saveAllCourses()
{
    QFile file("wszystkiekursy.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw FileWriteException("wszystkiekursy.txt");
    }

    QTextStream out(&file);
    for (auto i = allCourses.begin(); i != allCourses.end(); ++i) {
        out << i->getId() << ";" << i->getName() << ";" << i->getDescription() << "\n";
    }
    file.close();
}

void CourseManager::loadAllCourses()
{
    QFile file("wszystkiekursy.txt");
    if (!file.exists()) //jesli nasz plik nie istnieje to tworzymy kilka domyslnych kursow aby cos bylo
        allCourses.append(Course(nextId++, "Matematyka", "Podstawy algebry i analizy"));
        allCourses.append(Course(nextId++, "Fizyka", "Wprowadzenie do fizyki"));
        allCourses.append(Course(nextId++, "Programowanie", "Podstawy programowania w C++"));
        allCourses.append(Course(nextId++, "Chemia", "Podstawy chemii"));
        allCourses.append(Course(nextId++, "Język angielski", "Kurs podstawowego angielskiego"));
        saveAllCourses();
        return;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw FileOpenException("wszystkiekursy.txt");
    }

    QTextStream in(&file);
    allCourses.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(';');
        if (parts.size() < 3)
            continue;

        bool czyok;
        int id = parts[0].toInt(&czyok);
        if (!czyok) {
            throw FileReadException("Nieprawidłowy ID kursu w pliku wszystkiekursy.txt: " + parts[0].toStdString());
        }

        QString name = parts[1];
        QString description = parts.mid(2).join(";");

        if (id >= nextId)
            nextId = id + 1;

        allCourses.append(Course(id, name, description));
    }

    file.close();
}

bool CourseManager::removeCourseCompletely(int courseId)
{
    bool removedFromAllCourses = false;
    bool removedFromStudentCourses = false;

    //usuwamy z allCourses
    for (auto it = allCourses.begin(); it != allCourses.end(); ) {
        if (it->getId() == courseId) {
            it = allCourses.erase(it);
            removedFromAllCourses = true;
        } else {
            ++it;
        }
    }

    //usuwamy z studentCourses
    for (auto it = studentCourses.begin(); it != studentCourses.end(); ) {
        if (it->getId() == courseId) {
            it = studentCourses.erase(it);
            removedFromStudentCourses = true;
        } else {
            ++it;
        }
    }

    if (removedFromAllCourses) {
        saveAllCourses();
    }

    if (removedFromStudentCourses) {
        saveStudentCourses();
    }

    return removedFromAllCourses || removedFromStudentCourses;
}
