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
    ui->road_dropdown->addItems({"Valtatie 12 Kauppi", "Tie 65 Lielahti", "Pasilankatu Helsinki", "E12 Virveli Hämeenlinna", "E8 Pori"});

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
    delete graph;
}

void MainWindow::road(int index)
{
    //Road dropdownin tekemiset laitetaan tänne
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


void MainWindow::on_saveButton_clicked()
{
    placeholdername = QInputDialog::getText(this, "Input required!","Enter graph name:");
    emit saveButtonClicked();
}



void MainWindow::addtoCompare() {
    ui->CompareDropdown->addItem(placeholdername);
}



void MainWindow::on_CompareDropdown_activated(int index)
{

}

