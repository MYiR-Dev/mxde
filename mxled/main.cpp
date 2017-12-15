#include "mxleddialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MxLedDialog w(&a);
    w.show();

    return a.exec();
}
