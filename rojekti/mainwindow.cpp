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
    graph->drawGraph(series, ui->horizontalFrame);
}

void MainWindow::road(int index)
{
    //Road dropdownin tekemiset laitetaan tänne
    qDebug() << index;
}
