#include "mainwindow.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    model *m = new model();
    controller* controller = new class controller(m, w);
    w->show();
    return a.exec();
}
