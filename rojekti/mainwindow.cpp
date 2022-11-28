#include "mainwindow.h"
#include "qdir.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), currentButton_(Button::RoadMaintenance)
{
    ui->setupUi(this);
    connect(ui->road_dropdown, &QComboBox::currentIndexChanged,
            this, &MainWindow::road);

    connect(ui->roadmaintenance, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->roadcondition, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->averageTemperature, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->maximumTemperature, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->minimumTemperature, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->predictedtemperature, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->predictedwind, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->observedwind, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->observedcloudiness, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->precipitation, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->temperature_f, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->temperature_h, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);
    connect(ui->trafficmessages, &QRadioButton::clicked, this, &MainWindow::updateCurrentButton);

    ui->horizontalLayout->addWidget(chartview);

    // Add roads
    ui->road_dropdown->addItems({"Valtatie 12 Kauppi", "Tie 65 Lielahti", "Pasilankatu Helsinki", "E12 Virveli Hämeenlinna", "E8 Pori"});

    // Set default time to today
    ui->startTimeEdit->setDate(QDate::currentDate());
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime());
    loadCompareItems();
}

MainWindow::~MainWindow()
{
    delete ui;
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
    QMessageBox* typeselector = new QMessageBox();
    typeselector->addButton("Save normally", QMessageBox::YesRole);
    typeselector->addButton("Save as image", QMessageBox::AcceptRole);
    int test = typeselector->exec();
    QInputDialog window;
    int test2 =window.exec();
    qInfo() << test2;
    placeholdername = window.textValue();
    if(ui->CompareDropdown->findText(placeholdername) != -1 & test2 !=0) {
        qInfo() << placeholdername;
        QMessageBox::warning(this, "Error", "Name already used, delete previous one or use another name");
        return;
    }
    else if (test2 == 1)
    {emit saveButtonClicked(test);
        ui->CompareDropdown->addItem(placeholdername);}
}


void MainWindow::on_CompareDropdown_activated(int index)
{
    fileCreator* creator_ = new fileCreator;
    placeholdername = ui->CompareDropdown->currentText();
    QList<QString> emptylist = {};
    if(creator_->getImageNames(emptylist).contains(placeholdername)) {

        ui->horizontalLayout_5->removeWidget(chartview2);
        ui->horizontalLayout_5->addWidget(imagelabel);
        chartview2 = new QChartView();
            QPixmap pixmap("graphImages/" + placeholdername + ".png");

          imagelabel->setPixmap(pixmap);

    }
    else{

        ui->horizontalLayout_5->removeWidget(imagelabel);
        imagelabel = new QLabel();
        ui->horizontalLayout_5->addWidget(chartview2);
    emit compareDropdownActivated();
    }
}

void MainWindow::updateCurrentButton()
{
    if (ui->roadmaintenance->isChecked()) {
        currentButton_ = Button::RoadMaintenance;
    } else if (ui->roadcondition->isChecked()) {
        currentButton_ = Button::OverallRoadCondition;
    } else if (ui->averageTemperature->isChecked()) {
        currentButton_ = Button::AverageTemperature;
    } else if (ui->maximumTemperature->isChecked()) {
        currentButton_ = Button::MaximumTemperature;
    } else if (ui->minimumTemperature->isChecked()) {
        currentButton_ = Button::MinimumTemperature;
    } else if (ui->predictedtemperature->isChecked()) {
        currentButton_ = Button::PredictedTemperature;
    } else if (ui->predictedwind->isChecked()) {
        currentButton_ = Button::PredictedWind;
    } else if (ui->observedwind->isChecked()) {
        currentButton_ = Button::ObservedWind;
    } else if (ui->observedcloudiness->isChecked()) {
        currentButton_ = Button::ObservedCloudiness;
    } else if (ui->precipitation->isChecked()) {
        currentButton_ = Button::Precipitation;
    } else if (ui->temperature_f->isChecked()) {
        currentButton_ = Button::TemperatureForecast;
    } else if (ui->temperature_h->isChecked()) {
        currentButton_ = Button::TemperatureHistory;
    } else if (ui->trafficmessages->isChecked()) {
        currentButton_ = Button::TrafficMessages;
    } else {
        currentButton_ = Button::NaB;
    }
}


void MainWindow::on_deleteButton_clicked()
{
    placeholdername = ui->CompareDropdown->currentText();
    emit deleteButtonClicked();
}

//loads previously saved graph names and adds them to the CompareDropdown
void MainWindow::loadCompareItems() {
    ui->CompareDropdown->clear();
    ui->CompareDropdown->addItem("Current");
    placeholdername = "Current";
    fileCreator* temp = new fileCreator;
    QList<QString> graphs = temp->loadGraphNames();

   for(auto i : graphs) {
       ui->CompareDropdown->addItem(i);
   }

}

MainWindow::Button MainWindow::getCurrentButton()
{
    return currentButton_;
}

void MainWindow::on_GraphcomboBox_activated(int index)
{
    if(index == 0){graphtype = "line";}
    else if(index == 1){graphtype = "bar";}
    else if (index == 2) {graphtype = "scatter";}
    emit pushButtonClicked();
}

