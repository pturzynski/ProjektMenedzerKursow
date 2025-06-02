#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "loginwindow.h"
#include <QInputDialog>
#include <QMessageBox>

AdminWindow::AdminWindow(CourseManager *cm, Admin* adminUser, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::AdminWindow),
    cm(cm),
    adminUser(adminUser)
{
    ui->setupUi(this);
    QStringList headers = { "ID", "Nazwa", "Opis" };
    ui->kursyTableWidget->setColumnCount(3);
    ui->kursyTableWidget->setHorizontalHeaderLabels(headers);
    ui->kursyTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->kursyTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->kursyTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    fillCoursesTable();
}

AdminWindow::~AdminWindow()
{
    delete ui;
    delete adminUser;
}

void AdminWindow::fillCoursesTable()
{
    auto courses = cm->getAllCourses();
    ui->kursyTableWidget->setRowCount(courses.size());

    for (int i = 0; i < courses.size(); ++i) {
        const Course& c = courses.at(i);
        ui->kursyTableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->kursyTableWidget->setItem(i, 1, new QTableWidgetItem(c.getName()));
        ui->kursyTableWidget->setItem(i, 2, new QTableWidgetItem(c.getDescription()));
    }
}

void AdminWindow::on_dodajKursButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Dodaj kurs"),
                                         tr("Nazwa kursu:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) {
        QMessageBox::warning(this, tr("Błąd"), tr("Nazwa kursu nie może być pusta."));
        return;
    }

    QString description = QInputDialog::getMultiLineText(this, tr("Dodaj kurs"),
                                                         tr("Opis kursu:"), "", &ok);
    if (!ok || description.isEmpty()) {
        QMessageBox::warning(this, tr("Błąd"), tr("Opis kursu nie może być pusty."));
        return;
    }

    bool success = cm->addCourse(adminUser, name, description);
    if (success) {
        QMessageBox::information(this, tr("Sukces"), tr("Kurs dodany pomyślnie."));
        fillCoursesTable();
    } else {
        QMessageBox::warning(this, tr("Błąd"), tr("Nie udało się dodać kursu."));
    }
}

void AdminWindow::on_usunKursButton_clicked()
{
    bool ok;
    int courseId = QInputDialog::getInt(this, tr("Usuń kurs"),
                                        tr("Podaj ID kursu do usunięcia:"), 0, 0, 100000, 1, &ok);
    if (!ok) return;

    if (!adminUser->isAdmin()) {
        QMessageBox::warning(this, tr("Błąd"), tr("Nie masz uprawnień do usunięcia kursu."));
        return;
    }

    bool success = cm->removeCourseCompletely(courseId);
    if (success) {
        QMessageBox::information(this, tr("Sukces"), tr("Kurs usunięty pomyślnie."));
        fillCoursesTable();
    } else {
        QMessageBox::warning(this, tr("Błąd"), tr("Nie znaleziono kursu o podanym ID."));
    }
}


void AdminWindow::on_wylogujButton_clicked()
{
    LoginWindow *login = new LoginWindow(cm);
    login->show();
    this->close();
}


