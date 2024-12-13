#include "QtExcel.h"

QtExcel::QtExcel(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.setRow, &QPushButton::clicked, this, &QtExcel::on_setRow_clicked);
    connect(ui.rowEdit, &QLineEdit::textChanged, this, &QtExcel::editRow_textChanged);
    connect(ui.fillRandom, &QPushButton::clicked, this, &QtExcel::on_fillRandom_clicked);
	connect(ui.minimum, &QPushButton::clicked, this, &QtExcel::on_minimum_clicked);
	connect(ui.maximum, &QPushButton::clicked, this, &QtExcel::on_maximum_clicked);
	connect(ui.average, &QPushButton::clicked, this, &QtExcel::on_average_clicked);
	connect(ui.tableWidget, &QTableWidget::cellChanged, this, &QtExcel::on_setRow_clicked);
	connect(ui.editSearch, &QLineEdit::textChanged, this, &QtExcel::editSearch_textChanged);
	connect(ui.search, &QPushButton::clicked, this, &QtExcel::search_clicked);
	connect(ui.Ascending, &QRadioButton::toggled, this, &QtExcel::onAscendingToggled);
	connect(ui.Descending, &QRadioButton::toggled, this, &QtExcel::onDescendingToggled);
	connect(ui.sort, &QPushButton::clicked, this, &QtExcel::on_sort_clicked);

    table = new Table(&ui);
    
}

QtExcel::~QtExcel()
{}

void QtExcel::on_setRow_clicked() {
    
    if (rowCount == 0) {
        table->setTableSize(1, 1);
    }
    else
    {
        table->setTableSize(rowCount, 1);
    }
    
    table->render();

    

}
void QtExcel::editRow_textChanged(const QString &text) {
    bool ok;
    rowCount = text.toInt(&ok);
    if (ok) {
        qDebug() << "Converted value" << rowCount;
    }
    else
    {
        qDebug() << "Conversion failed";

    }

}
void QtExcel::on_fillRandom_clicked() {

	QRandomGenerator* generator = QRandomGenerator::global();
	generator->generate();
	QList<QString> arr = QList<QString>(table->getRowCount());

    for (auto& var : arr)
    {
        var = QString::number(generator->bounded(1,100));
    }

	table->fillColumn(arr,0);
	table->render();

}
void QtExcel::on_minimum_clicked() {
	int min = INT_MAX;
    for (int i = 0; i < table->getRowCount(); i++)
    {
        for (int j = 0; j < table->getColumnCount(); j++)
        {
			bool ok;
			int ll = table->getCell(i, j).toInt(&ok);
            if (ok) {
                if (ll < min) {
                    min = ll;
                }
            }
            else
            {
				table->setCell(i, j, "Error");
            }
			
        }
    }
	if (min == INT_MAX)
	{
		QMessageBox(QMessageBox::Icon::Information, "Minimum", "No numbers in table").exec();
		return;
	}
	QMessageBox(QMessageBox::Icon::Information, "Minimum", "Minimum value is " + QString::number(min)).exec();
	table->render();
}
void QtExcel::on_maximum_clicked() {
    int max = INT_MIN;
    for (int i = 0; i < table->getRowCount(); i++)
    {
        for (int j = 0; j < table->getColumnCount(); j++)
        {
            bool ok;
            int ll = table->getCell(i, j).toInt(&ok);
            if (ok) {
                if (ll > max) {
                    max = ll;
                }
            }
            else
            {
                table->setCell(i, j, "Error");
            }

        }
    }
    if (max == INT_MIN)
    {
        QMessageBox(QMessageBox::Icon::Information, "Maximum", "No numbers in table").exec();
        return;
    }
    QMessageBox(QMessageBox::Icon::Information, "Maximum", "Maximum value is " + QString::number(max)).exec();
    table->render();
}
void QtExcel::on_average_clicked() {
	int sum = 0;
	int count = 0;
	for (int i = 0; i < table->getRowCount(); i++)
	{
		for (int j = 0; j < table->getColumnCount(); j++)
		{
			bool ok;
			int ll = table->getCell(i, j).toInt(&ok);
			if (ok) {
				sum += ll;
				count++;
			}
			else
			{
				table->setCell(i, j, "Error");
			}
		}
	}
	if (count == 0)
	{
		QMessageBox(QMessageBox::Icon::Information, "Average", "No numbers in table").exec();
		return;
	}
	QMessageBox(QMessageBox::Icon::Information, "Average", "Average value is " + QString::number(sum / count)).exec();
	table->render();
}
void QtExcel::editSearch_textChanged(const QString& text) {
	bool ok;
	searchVall = text.toInt(&ok);
	if (ok) {
		qDebug() << "Converted value" << searchVall;
	}
	else
	{
		qDebug() << "Conversion failed";
	}
}
void QtExcel::search_clicked() {
	int count = 0;
	QString answer = "";
	for (int i = 0; i < table->getRowCount(); i++)
	{
		for (int j = 0; j < table->getColumnCount(); j++)
		{
			bool ok;
			int ll = table->getCell(i, j).toInt(&ok);
			if (ok) {
				if (ll == searchVall) {
					count++;
					answer += QString("%1:%2\n").arg(i+1).arg(j+1);
				}
				
			}
			else
			{
				table->setCell(i, j, "Error");
			}
		}
	}
	if (count == 0)
	{
		QMessageBox(QMessageBox::Icon::Information, "Search", "No numbers in table").exec();
		return;
	}
	QMessageBox(QMessageBox::Icon::Information, "Search", "Value " + QString::number(searchVall) + " found " + QString::number(count) + " times" +"\n"+answer).exec();
	table->render();
}
void QtExcel::onAscendingToggled() {

	isAscendingSort = true;
}
void QtExcel::onDescendingToggled() {

	isAscendingSort = false;
}
void QtExcel::on_sort_clicked() {

	table->sort(!isAscendingSort);

}







