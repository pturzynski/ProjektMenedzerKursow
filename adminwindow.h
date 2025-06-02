#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "BusinessLogic/coursemanager.h"
#include "BusinessLogic/admin.h"
#include "BusinessLogic/user.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(CourseManager* cm, Admin* adminUser, QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_dodajKursButton_clicked();

    void on_usunKursButton_clicked();

    void on_wylogujButton_clicked();

private:
    Ui::AdminWindow *ui;
    CourseManager *cm;
    Admin* adminUser;
    void fillCoursesTable();
};

#endif // ADMINWINDOW_H
