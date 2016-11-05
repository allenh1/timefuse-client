#include "schedulinggrid.h"
#include <QApplication>
#include <QDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    schedulingGrid w;
    w.show();

    return a.exec();
}
