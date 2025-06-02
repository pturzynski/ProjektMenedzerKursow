#include "AdminWindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CourseManager *manager = new CourseManager();
    LoginWindow loginWindow(manager);
    loginWindow.show();
    return a.exec();
}
