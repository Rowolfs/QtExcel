#include "QtExcel.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtExcel w;
    w.show();
    return a.exec();
}


