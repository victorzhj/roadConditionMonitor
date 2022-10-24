#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraph.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

