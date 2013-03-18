#include "qt_calculator.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QT_calculator w;
    w.show();
    return a.exec();
}
