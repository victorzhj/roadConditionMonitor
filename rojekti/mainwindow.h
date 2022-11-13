#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "qchartview.h"
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString placeholdername;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawGraph(model *model_, bool WhichGraph);
    std::pair<QDateTime, QDateTime> getTimeRange();
    void loadCompareItems();
    void addtoCompare();
public slots:
    void road(int index);

private slots:
    void on_pushButton_clicked();

    void on_roadmaintenance_toggled(bool checked);

    void on_saveButton_clicked();



    void on_CompareDropdown_activated(int index);

    void on_deleteButton_clicked();

signals:
    void pushButtonClicked();
    void saveButtonClicked();
    void compareDropdownActivated();
    void deleteButtonClicked();

private:
    Ui::MainWindow *ui;
    QChartView* chartview = new QChartView();
    QChartView* chartview2 = new QChartView();
};
#endif // MAINWINDOW_H
