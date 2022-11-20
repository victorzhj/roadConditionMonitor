#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "filecreator.h"
#include "model.h"
#include "mainwindow.h"
#include "jsonnetworker.h"

class controller : public QObject
{
    Q_OBJECT
public:
    controller(model *model, MainWindow *view, QObject *parent = nullptr);
    void updateGraph(int i);
    void getData();
    void compareDropdownActivated();
    void deleteButtonClicked();
private:
    model* model_;
    MainWindow* view_;
    fileCreator* creator_;

public slots:
    void GraphButtonClicked();
    void saveButtonClicked();
signals:

};

#endif // CONTROLLER_H
