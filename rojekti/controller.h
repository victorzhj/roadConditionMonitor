#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "mainwindow.h"
#include "creategraph.cpp"
#include "jsonnetworker.h"

class controller : public QObject
{
    Q_OBJECT
public:
    controller(model *model, MainWindow *view, QObject *parent = nullptr);
    void updateGraph(int i, string startDate = "");
    void getData();
    void compareDropdownActivated();
    void deleteButtonClicked();
    void deletePreferenceButtonClicked();
    void PreferenceButtonClicked(int i, int j, int h, int k);

private:
    model* model_;
    MainWindow* view_;
    fileCreator* creator_;
    std::string typeoftime;

public slots:
    void GraphButtonClicked();
    void saveButtonClicked(int i);
signals:

};

#endif // CONTROLLER_H
