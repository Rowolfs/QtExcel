#pragma once
#include <QDebug>
#include <QString>
#include <QtWidgets/QMainWindow>
#include "ui_QtExcel.h"
#include <iostream>
#include <QThread>
#include <algorithm>
class Table : public QObject
{
    Q_OBJECT


public:
    Table() {};

    Table(Ui::QtExcelClass* ui);

    void setTableSize(int rowCounts, int columnCount);

    void render() {
        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(columnCount);
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++) {
               
                    if (!ui->tableWidget->item(i, j)) {
                        ui->tableWidget->setItem(i, j, new QTableWidgetItem());
                    }
                    ui->tableWidget->item(i, j)->setText(data[i][j]);
                
                
            }
        }

    }

    void fillColumn(QList<QString> values, int collumn);
	int getRowCount() { return rowCount; }
	int getColumnCount() { return columnCount; }
	QString getCell(int row, int collumn) { return data[row][collumn]; }
    void setCell(int row, int column, const QString& value) {
        // Обновляем данные в массиве
        data[row][column] = value;

        // Получаем ячейку таблицы
        QTableWidgetItem* item = ui->tableWidget->item(row, column);

        // Если ячейка не существует, создаем ее
        if (!item) {
            item = new QTableWidgetItem(); // Создаем новую ячейку
            ui->tableWidget->setItem(row, column, item); // Устанавливаем ее в таблицу
        }

        // Устанавливаем новое значение текста в ячейке
        item->setText(value);
    }
    void sort(bool reverse) {
        for (int k = 0; k < rowCount; k++)
        {


            for (int i = 0; i < rowCount-k; i++)
            {
                for (int j = 0; j < columnCount; j++)
                {

                    if (j == columnCount - 1 && i == rowCount - 1) {
                        continue;
                    }
                    else if (j == columnCount - 1)
                    {
                        swapIntForSort(data[i][j], data[i + 1][j], reverse);
                    }
                    else
                    {
                        swapIntForSort(data[i][j], data[i][j + 1], reverse);
                    }
                }
            }
        }
        this->render();
    }


private:
    int rowCount = 0;
    int columnCount = 0;
    Ui::QtExcelClass* ui;
    QList<QList<QString>> data;
    void swapIntForSort(QString& a, QString& b, bool reverse = false) {
        bool ok1, ok2;
        int val1 = a.toInt(&ok1); // Преобразуем строку a в число
        int val2 = b.toInt(&ok2); // Преобразуем строку b в число

        QString temp;

        // Если оба значения можно преобразовать в числа
        if (ok1 && ok2) {
            if (reverse) {
                // Если reverse = true, сортируем по убыванию
                if (val1 < val2) {
                    temp = b;
                    b = a;
                    a = temp;
                }
            }
            else {
                // Если reverse = false, сортируем по возрастанию
                if (val1 > val2) {
                    temp = b;
                    b = a;
                    a = temp;
                }
            }
        }
        else if(ok2)
        {
            temp = b;
            b = a;
            a = temp;
        }
        
        
        
    }


private slots:
    void tableWidget_itemEdit(QTableWidgetItem* item);


};


