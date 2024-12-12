#include "QtExcel.h"



QtExcel::QtExcel(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.setRow, &QPushButton::clicked, this, &QtExcel::on_setRow_clicked);
    connect(ui.rowEdit, &QLineEdit::textChanged, this, &QtExcel::editRow_textChanged);
    
    table = new Table(1,1,&ui);
}

QtExcel::~QtExcel()
{}





void QtExcel::on_setRow_clicked() {
    
    table->setTableSize(rowCount, 1);
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



