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
    if (!item) return;  
    int row = item->row();
    int column = item->column();
    QString cellValue = item->text();  // Получаем новое значение ячейки
    if (row >= 0 && row < data.size() && column >= 0 && column < data[row].size()) {
        cellValue = QtExcel::checkTableValue(cellValue, row, column);
        data[row][column] = cellValue;
        item->setText(cellValue); // Обновляем данные
    }
	
    
}

void Table::fillColumn(QList<QString> values,int collumn) {

    if (collumn > data[0].size()) {
        return;
    }
	int deep = std::min(data.size(), values.size());
    for (int i = 0; i < deep; i++)
    {
        data[i][collumn] = values[i];
    }
    

}

void Table::render() {
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


void Table::setCell(int row, int column, const QString& value) {
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

void Table::sort(bool reverse) {


}


void Table::swapIntForSort(QString& a, QString& b, bool reverse) {
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
    else if (ok2)
    {
        temp = b;
        b = a;
        a = temp;
    }



}
void Table::fillRow(QList<QString> values, int row) {
	if (row > data.size()) {
		return;
	}
	int deep = std::min(data[row].size(), values.size());
	for (int i = 0; i < deep; i++)
	{
		data[row][i] = values[i];
	}
}
