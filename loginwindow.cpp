#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "AdminWindow.h"
#include "studentwindow.h"
#include <QMessageBox>
#include "BusinessLogic/exceptions.h"

LoginWindow::LoginWindow(CourseManager *cm, QWidget *parent)
    : QMainWindow(parent),
    cm(cm),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    try{
        if(username == "admin" && password == "admin"){
            Admin* adminUser = new Admin(username, password);
            AdminWindow *adminWindow = new AdminWindow(cm, adminUser);
            adminWindow->show();
            this->close();
        }

        else if(username == "student" && password == "student"){
            StudentWindow *studentWindow = new StudentWindow(cm); //
            studentWindow->show();
            this->close();
        }

        else{
            throw LoginFailedException("Nieprawidłowy login lub hasło");
        }
    }
    catch (const LoginFailedException &exc) {
        QMessageBox::critical(this, "Błąd loowania", QString::fromStdString(exc.what()));
    }
}
