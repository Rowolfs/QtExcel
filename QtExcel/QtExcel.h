#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include "Table.h"
#include <iostream>
#include <QRandomGenerator>
#include <qmessagebox.h>
#include "User.h"
#include "algorithm"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QFileDialog>

// This is qtExcel++

class Table;



class QtExcel : public QMainWindow
{
    Q_OBJECT

public:
    QtExcel(QWidget* parent = nullptr);
    ~QtExcel();






    static QString checkTableValue(QString cellValue, int row, int column) {
        QRegularExpression idRegex("^\\d+$");
        QRegularExpression nameRegex("^[A-ZА-Я][a-zа-я]+$");
        QRegularExpression surnameRegex("^[A-ZА-Я][a-zа-я]+$");
        QRegularExpression surname2Regex("^[A-ZА-Я][a-zа-я]+$");
        QRegularExpression phoneRegex("^\\+?\\d{10,15}$");
        QRegularExpression emailRegex("^[\\w.%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
        if (cellValue == "") {
            return "Error";
        }
        switch (column)
        {
        case 0:
            // Проверка на id (число)
            if (!idRegex.match(cellValue).hasMatch()) {
                return "Error: Invalid ID";
            }
            break;

        case 1:
            // Проверка на имя (name, только буквы)
            if (!nameRegex.match(cellValue).hasMatch()) {
                return "Error: Invalid Name";
            }
            break;

        case 2:
            // Проверка на фамилию (surname, только буквы)
            if (!surnameRegex.match(cellValue).hasMatch() ) {
                return "Error: Invalid Surname";
            }
            break;

        case 3:
            // Проверка на вторую фамилию (surname2, только буквы или пусто)
            if (!surname2Regex.match(cellValue).hasMatch() ) {
                return "Error: Invalid Surname2";
            }
            break;

        case 4:
            // Проверка на телефонный номер (phonenumber, формат +1234567890)
            if (!phoneRegex.match(cellValue).hasMatch()) {
                return "Error: Invalid Phone Number";
            }
            break;

        case 5:
            // Проверка на email
            if (!emailRegex.match(cellValue).hasMatch()) {
                return "Error: Invalid Email";
            }
            break;
        }

        return cellValue; // Возвращаем исходное значение, если нет ошибок
    }

    

private:
    int rowCount = 0;
    Ui::QtExcelClass ui;
    Table* table;
    QString searchVall;
    bool isAscendingSort = true;
	QList<User*> users;
	void checkTableValues();

	bool isEmailSort = false;
	bool isFamilySort = false;
	bool isNameSort = false;
	bool isPhoneNumberSort = false;
	bool isSurnameSort = false;
	bool isIdsort = true;

private slots:
    void on_setRow_clicked();
    void editRow_textChanged(const QString &text);
    void on_fillRandom_clicked();
	void on_minimum_clicked();
	void on_maximum_clicked();
	void on_average_clicked();
	void editSearch_textChanged(const QString& text);
	void search_clicked();
    void onAscendingToggled();
    void onDescendingToggled();
    void on_sort_clicked();
	void on_DeleteDuplicates_clicked();
	void on_jsonOutput_clicked();
	void on_jsonInput_clicked();

    void onEmailRadioButtonToggled();
	void onFamilyRadioButtonToggled();
	void onNameRadioButtonToggled();
	void onPhoneNumberradioButtonToggled();
	void onSurnamesRadioButtonToggled();
	void onIdRadioButtonToggled();

};
