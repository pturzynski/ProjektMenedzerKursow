#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include "BusinessLogic/user.h"
#include "BusinessLogic/admin.h"
#include "BusinessLogic/student.h"
#include "BusinessLogic/coursemanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(CourseManager *cm, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();

private:
    CourseManager* cm;
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H
