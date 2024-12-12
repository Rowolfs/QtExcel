#include "Table.h"

void Table::setTableSize(int rowCounts, int columnCount) {

    this->columnCount = columnCount;
    this->rowCount = rowCounts;
    data = QList<QList<int>>();
    for (int i = 0; i < rowCount; ++i) {
        data.append(QList<int>(columnCount, 0));
        for (int j = 0; j < columnCount; j++) {
            data[i].append(0);
        }

    }
}

void Table::tableWidget_cellEdit(int row, int collumn) {
    QString cellValue = ui->tableWidget->item(row, collumn)->text();
    bool ok;
    int value = cellValue.toInt(&ok);
    if (ok) {
        qDebug() << "Converted value" << value;
        data[row][collumn] = value;
    }
    else
    {
        qDebug() << "Conversion failed";

    }



}

Table::Table(int rowCounts, int columnCount, Ui::QtExcelClass* ui) {
    this->columnCount = columnCount;
    this->rowCount = rowCounts;
    this->ui = ui;
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &Table::tableWidget_cellEdit);
    for (int i = 0; i < rowCount; ++i) {
        data.append(QList<int>(columnCount, 0));
        for (int j = 0; j < columnCount; j++) {
            data[i].append(0);
        }

    }
}