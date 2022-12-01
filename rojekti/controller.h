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
    /**
     * @brief controller constructor
     * @param model the "schema"
     * @param view the mainwindow
     * @param parent
     */
    controller(model *model, MainWindow *view, QObject *parent = nullptr);
    /**
     * @brief updateGraph
     * @param i determines which chart we are drawing on (upper or lower one)
     * @param endDate QDateTime in the form of a string to tell us when the graph was drawn
     */
    void updateGraph(int i, string endDate = "");
    void compareDropdownActivated();
    void deleteButtonClicked();
    void deletePreferenceButtonClicked();
    void PreferenceButtonClicked(int roaddropdownindex, int grapdropdownindex, int roadmaintenancetypeindex, int forecastdropdownindex, int messagetypedropdownindex);

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
