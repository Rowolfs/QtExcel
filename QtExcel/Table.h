#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include <iostream>
class Table : public QObject
{
    Q_OBJECT


public:
    Table() {};

    Table(int rowCounts, int columnCount, Ui::QtExcelClass* ui);

    void setTableSize(int rowCounts, int columnCount);

    void render() {
        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(columnCount);


    }

private:
    int rowCount;
    int columnCount;
    Ui::QtExcelClass* ui;
    QList<QList<int>> data;

private slots:
    void tableWidget_cellEdit(int row, int collumn);


};


