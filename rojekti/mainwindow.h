#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qchartview.h"
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include "qlabel.h"
#include "filecreator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString placeholdername;
    std::string graphtype = "line";
    QChartView* chartview = new QChartView();
    QChartView* chartview2 = new QChartView();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::pair<QDateTime, QDateTime> getTimeRange();
    void loadCompareItems();
    void addtoCompare();
public slots:
    void road(int index);
    void on_CompareDropdown_activated(int index);


private slots:
    void on_pushButton_clicked();

    void on_roadmaintenance_toggled(bool checked);

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_GraphcomboBox_activated(int index);

signals:
    void pushButtonClicked();
    void saveButtonClicked(int i);
    void compareDropdownActivated();
    void deleteButtonClicked();

private:
    Ui::MainWindow *ui;

    QLabel* imagelabel = new QLabel();
};
#endif // MAINWINDOW_H
