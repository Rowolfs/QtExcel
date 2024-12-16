#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include <iostream>
#include <QThread>
#include <algorithm>
#include "QtExcel.h"
class Table : public QObject
{
    Q_OBJECT


public:
    Table() {};

    Table(Ui::QtExcelClass* ui);

    void setTableSize(int rowCounts, int columnCount);
	void fillRow(QList<QString> values, int row);
    void fillColumn(QList<QString> values, int collumn);
    int getRowCount() { return rowCount; }
    int getColumnCount() { return columnCount; }
    QString getCell(int row, int collumn) { return data[row][collumn]; }
	void render();
	void sort(bool reverse = false);
	void setCell(int row, int column, const QString& value);
    QList<QList<QString>> getData() const { return data;}

private:
    int rowCount = 0;
    int columnCount = 0;
    Ui::QtExcelClass* ui;
    QList<QList<QString>> data;
    void swapIntForSort(QString& a, QString& b, bool reverse = false);
        


private slots:
    void tableWidget_itemEdit(QTableWidgetItem* item);


};


