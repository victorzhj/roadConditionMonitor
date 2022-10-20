#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creategraph.cpp"

vector<int> xaxis = {1,2,3,4,5,6,7,8,9};
vector<int> yaxis = {10,20,30,40,50,60,70,80,90};
map<int,int> messages = {{1,2},{2,6},{3,7},{0,10}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateGraph *graph = new CreateGraph();
    //graph->drawGraph(xaxis, yaxis, ui->horizontalFrame);
    graph->drawBarGraph(messages, ui->horizontalFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
}


