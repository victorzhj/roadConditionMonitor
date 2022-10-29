#include "mainwindow.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    model* model = new class model(); // Pitäiskö muuttujan nimi olla eri kun luokan nimi??????? Also mikä new *class*???
    controller* controller = new class controller(model, w);
    w->show();
    return a.exec();
}
