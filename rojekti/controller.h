#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "mainwindow.h"

class controller : public QObject
{
    Q_OBJECT
public:
    controller(model *model, MainWindow *view, QObject *parent = nullptr);
    void updateGraph();
private:
    model* model_;
    MainWindow* view_;
signals:

};

#endif // CONTROLLER_H
