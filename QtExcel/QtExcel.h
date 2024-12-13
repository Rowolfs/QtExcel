#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include "Table.h"
#include <iostream>
#include <QRandomGenerator>
#include <qmessagebox.h>

// This is qtExcel++





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
    int searchVall;
    bool isAscendingSort = true;

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

};
