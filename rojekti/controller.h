#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "mainwindow.h"
#include "creategraph.cpp"

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
    /**
     * @brief Receives a signal from the view when the compare dropdown is activated and it will
     * change the lower graph according to the selection
     */
    void compareDropdownActivated();
    /**
     * @brief deletes the saved graph that is displayed on the lower chart
     */
    void deleteButtonClicked();
    /**
     * @brief deletes the currently selected preference
     */
    void deletePreferenceButtonClicked();
    /**
     * @brief Saves the current search options as a preference, receives signal with indexes from view
     * @param roaddropdownindex
     * @param grapdropdownindex
     * @param roadmaintenancetypeindex
     * @param forecastdropdownindex
     * @param messagetypedropdownindex
     */
    void PreferenceButtonClicked(int roaddropdownindex, int grapdropdownindex, int roadmaintenancetypeindex, int forecastdropdownindex, int messagetypedropdownindex);

private:
    model* model_;
    MainWindow* view_;
    fileCreator* creator_;
    std::string typeoftime;

public slots:
    /**
     * @brief Graphs into the upper chart based on user input in the main window
     */
    void GraphButtonClicked();
    /**
     * @brief Saves the graph that is currently being displayed in the upper chart
     * @param i tells us
     */
    void saveButtonClicked(int i, QString name);
signals:

};

#endif // CONTROLLER_H
