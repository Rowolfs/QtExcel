#include "Table.h"
Table::Table(Ui::QtExcelClass* ui) {
    this->ui = ui;
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &Table::tableWidget_itemEdit);
    data = QList<QList<QString>>();
}

void Table::setTableSize(int rowCount, int columnCount) {
    // Найти последнюю заполненную строку и столбец
    int rowLast = 0;
    int columnLast = 0;

    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] != "") {
                rowLast = std::max(rowLast, i);
                columnLast = std::max(columnLast, j);
            }
        }
    }

    // Увеличить количество строк, если нужно
    while (data.size() < rowCount) {
        data.append(QList<QString>(columnCount, ""));
    }

    // Увеличить количество столбцов в существующих строках, если нужно
    for (int i = 0; i < data.size(); i++) {
        while (data[i].size() < columnCount) {
            data[i].append("");
        }
    }

    // Обрезать строки и столбцы, если нужно
    if (data.size() > rowCount) {
        data.erase(data.begin() + rowLast + 1, data.end());
    }
    
    for (int i = 0; i < data.size(); i++) {
        if (data[i].size() > columnCount) {
            data[i].erase(data[i].begin() + columnLast + 1, data[i].end());
        }
    }

    this->rowCount = data.size();
    this->columnCount = data[0].size();
}

void Table::tableWidget_itemEdit(QTableWidgetItem* item) {
    if (!item) return;  // Проверяем, что элемент существует
    int row = item->row();
    int column = item->column();
    QString cellValue = item->text();  // Получаем новое значение ячейки
    if (row >= 0 && row < data.size() && column >= 0 && column < data[row].size()) {
        data[row][column] = cellValue;  // Обновляем данные
    }
}

void Table::fillColumn(QList<QString> values,int collumn) {

    if (data.size() == 0) {
        setTableSize(1, 1);
        this->render();
    }

    if (collumn > data[0].size()) {
        return;
    }
	int deep = std::min(data.size(), values.size());
    for (int i = 0; i < deep; i++)
    {
        data[i][collumn] = values[i];
    }
    

}




