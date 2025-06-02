#include "studentwindow.h"
#include "ui_studentwindow.h"
#include <QMessageBox>

StudentWindow::StudentWindow(CourseManager* cm, Student *studentUser, QWidget *parent)
    : QMainWindow(parent),
    cm(cm),
    ui(new Ui::StudentWindow),
    studentUser(studentUser)
{
    ui->setupUi(this);

    //ogarniecie gui aby sie skalowalo
    QStringList headers;
    headers << "ID:" << "Nazwa: " << "Opis: ";

    //wszystkie kursy
    ui->listaKursowTableWidget->setColumnCount(3);
    ui->listaKursowTableWidget->setHorizontalHeaderLabels(headers);
    ui->listaKursowTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->listaKursowTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->listaKursowTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    //moje kursy
    ui->mojeKursyTableWidget->setColumnCount(3);
    ui->mojeKursyTableWidget->setHorizontalHeaderLabels(headers);
    ui->mojeKursyTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->mojeKursyTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->mojeKursyTableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    fillKursyTable();
    fillMojeKursyTable();
}

StudentWindow::~StudentWindow()
{
    delete ui;
}

void StudentWindow::on_wylogujButton_clicked()
{
    LoginWindow *login = new LoginWindow(cm);
    login->show();
    this->close();
}

void StudentWindow::fillKursyTable()
{
    QList<Course> allCourses = cm->getAllCourses();

    ui->listaKursowTableWidget->setRowCount(allCourses.size());

    for (int row = 0; row < allCourses.size(); ++row) {
        const Course& course = allCourses.at(row);
        ui->listaKursowTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(course.getId())));
        ui->listaKursowTableWidget->setItem(row, 1, new QTableWidgetItem(course.getName()));
        ui->listaKursowTableWidget->setItem(row, 2, new QTableWidgetItem(course.getDescription()));
    }
}

void StudentWindow::fillMojeKursyTable()
{
    QList<Course> studentCourses = cm->getStudentCourses();

    ui->mojeKursyTableWidget->setRowCount(studentCourses.size());

    for (int row = 0; row < studentCourses.size(); ++row) {
        const Course& course = studentCourses.at(row);
        ui->mojeKursyTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(course.getId())));
        ui->mojeKursyTableWidget->setItem(row, 1, new QTableWidgetItem(course.getName()));
        ui->mojeKursyTableWidget->setItem(row, 2, new QTableWidgetItem(course.getDescription()));
    }
}

void StudentWindow::on_zapiszKursButton_clicked()
{
    int selectedRow = ui->listaKursowTableWidget->currentRow();
    // sprawdzanie czy zaznaczony jest jakis kurs
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Brak wyboru", "Wybierz kurs z listy, aby się zapisać.");
        return;
    }

    int id = ui->listaKursowTableWidget->item(selectedRow, 0)->text().toInt();

    bool success = cm->enrollStudent(id);
    if (!success) {
        QMessageBox::warning(this, "Błąd", "Nie można zapisać się na ten kurs.");
        return;
    }

    fillKursyTable();
    fillMojeKursyTable();

    QMessageBox::information(this, "Sukces", "Zapisano na kurs: ");
}
