#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::dataOfStudent)
{
    ui->setupUi(this);


    QRegularExpression regex("^[^0-9]*$"); // Разрешает любые символы, кроме цифр
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_2->setMaxLength(100);

    QRegularExpression regex1("^[0-9]{0,9}$"); // Разрешает от 0 до 10 цифр
    QRegularExpressionValidator *validator1 = new QRegularExpressionValidator(regex1, this);
    ui->lineEdit->setValidator(validator1);
    ui->lineEdit->setMaxLength(9);
    QIntValidator *intValidator2 = new QIntValidator(1, 4, this);
    ui->lineEdit_4->setValidator(intValidator2);
    ui->lineEdit_4->setMaxLength(1);
    QIntValidator *intValidator3 = new QIntValidator(1, 10, this);
    ui->lineEdit_5->setValidator(intValidator3);
    ui->lineEdit_5->setMaxLength(2);
    QDoubleValidator *doubleValidator1 = new QDoubleValidator(0.0, 10.0, 2, this);
    ui->lineEdit_6->setValidator(doubleValidator1);
    ui->lineEdit_6->setMaxLength(5);


    this->setStyleSheet("background-color: #F9F6D6;");
    ui->lineEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->lineEdit_2->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->lineEdit_4->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->lineEdit_5->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->lineEdit_6->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->dateEdit->setStyleSheet("background-color: rgb(255, 255, 255);");
    ui->pushButton->setStyleSheet("background-color: rgb(255, 255, 255);");
    // Проверка ввода
    connect(ui->lineEdit_6, &QLineEdit::textChanged, this, [=]() {
        bool ok;
        double value = ui->lineEdit_6->text().toDouble(&ok);
        if (ok && (value < 0.0 || value > 10.0)) {
            // Сброс значения, если оно вне допустимого диапазона
            ui->lineEdit_6->setText("");
        }
    });

    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, [=]() {
        bool ok;
        double value = ui->lineEdit_4->text().toInt(&ok);
        if (ok && (value < 1 || value > 4)) {
            // Сброс значения, если оно вне допустимого диапазона
            ui->lineEdit_4->setText("");
        }
    });

    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, [=]() {
        bool ok;
        double value = ui->lineEdit_5->text().toInt(&ok);
        if (ok && (value < 1 || value > 10)) {
            // Сброс значения, если оно вне допустимого диапазона
            ui->lineEdit_5->setText("");
        }
    });

    // Подключение сигнала нажатия кнопки к слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onSubmit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Слот для обработки нажатия кнопки
void MainWindow::onSubmit()
{
    // Получение данных из полей
    QString data1 = ui->lineEdit->text();
    QString data2 = ui->lineEdit_2->text();
    QString data4 = ui->lineEdit_4->text();
    QString data5 = ui->lineEdit_5->text();
    QString data6 = ui->lineEdit_6->text();
    // Получение даты
    QDate date = ui->dateEdit->date(); // Получение даты из QDateEdit
    QString dateString = date.toString("dd.MM.yyyy"); // Форматирование даты

    // Очистка полей
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->dateEdit->setDate(QDate(2000, 1, 1));
}
