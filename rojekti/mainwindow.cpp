#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraph.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->road_dropdown, &QComboBox::currentIndexChanged,
            this, &MainWindow::road);
    ui->horizontalLayout->addWidget(chartview);

    // Add roads
    ui->road_dropdown->addItems({"Sijainti 1", "Sijainti 2"});

    // Set default time to today
    ui->startTimeEdit->setDate(QDate::currentDate());
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawGraph(model* model_)
{
    CreateGraph *graph = new CreateGraph();
    QLineSeries* series = new QLineSeries();
    for (auto& point : model_->getChart()) {
            series->append(point);
        }
    graph->drawGraph(series, chartview);
    /*QBarSet* axisy = new QBarSet("");
    for (auto& point : model_->getChart()) {
            axisy->append(point.y());
            qDebug() << point.y();
        }
    QBarSeries* series = new QBarSeries(axisy);
    graph->drawBarGraph(series, chartview);*/
}

void MainWindow::road(int index)
{
    //Road dropdownin tekemiset laitetaan tänne
    qDebug() << index;
}

void MainWindow::on_pushButton_clicked()
{
        emit pushButtonClicked();
}


void MainWindow::on_roadmaintenance_toggled(bool checked)
{
    ui->type_pick->setEnabled(checked);
}

std::pair<QDateTime, QDateTime> MainWindow::getTimeRange() {
    QDateTime start = ui->startTimeEdit->dateTime();
    QDateTime end = ui->endTimeEdit->dateTime();
    return std::make_pair(start, end);
}

