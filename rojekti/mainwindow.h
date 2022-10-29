#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "qchartview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawGraph(model *model_);
    std::pair<QDateTime, QDateTime> getTimeRange();

public slots:
    void road(int index);

private slots:
    void on_pushButton_clicked();

    void on_roadmaintenance_toggled(bool checked);

signals:
    void pushButtonClicked();

private:
    Ui::MainWindow *ui;
    QChartView* chartview = new QChartView();
};
#endif // MAINWINDOW_H
