#include "mainwindow.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    model* model = new class model();
    controller* controller = new class controller(model, w);
    model->jsonGetData();
    w->show();
    return a.exec();
}
