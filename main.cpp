#include <QDebug>
#include <QApplication>
#include "RenderWidget.h"
#include "C3DSReader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RenderWidget w;
    w.show();
    return a.exec();
}
