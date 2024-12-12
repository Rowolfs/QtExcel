#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include "Table.h"
#include <iostream>





class QtExcel : public QMainWindow
{
    Q_OBJECT

public:
    QtExcel(QWidget *parent = nullptr);
    ~QtExcel();

private:
    int rowCount = 0;
    Ui::QtExcelClass ui;
    Table* table;
   
private slots:
    void on_setRow_clicked();
    void editRow_textChanged(const QString &text);
    
};
