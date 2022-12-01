#include "mainwindow.h"
#include "qdir.h"
#include "qjsonobject.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), currentButton_(Button::RoadMaintenance)
{
    ui->setupUi(this);

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

    connect(ui->trafficmessages, &QRadioButton::toggled, this, &MainWindow::on_trafficmessage_toggled);

    ui->horizontalLayout->addWidget(chartview);

    // Add roads
    ui->road_dropdown->addItems({"Valtatie 12 Kauppi", "E12 Pirkkala", "Tie 45 Helsinki", "E12 Virveli Hämeenlinna", "E8 Pori"});

    ui->fHoursSelect->addItems(forecastIntervals);
    ui->fHoursSelect->setEnabled(false);

    QStringList typeTexts;
    QStringList messageTypeTexts;

    for (std::map<std::string, std::string> i: tasks) {
        typeTexts.append(QString::fromStdString(i.at("nameEn")));
    }

    for (std::map<std::string, std::string> i: messages) {
        messageTypeTexts.append(QString::fromStdString(i.at("nameEn")));
    }

    ui->type_pick->addItems(typeTexts);
    ui->messagetype_pick->addItems(messageTypeTexts);
    ui->messagetype_pick->setEnabled(false);

    // Set default time to today
    ui->startTimeEdit->setDate(QDate::currentDate());
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime());
    loadCompareItems();
    loadPreferences();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_graphButton_clicked()
{
    ui->horizontalLayout->removeWidget(chartview);
    chartview = new QChartView();
    ui->horizontalLayout->addWidget(chartview);
        emit graphButtonClicked();
}


void MainWindow::on_roadmaintenance_toggled(bool checked)
{
    ui->type_pick->setEnabled(checked);
}

void MainWindow::on_trafficmessage_toggled(bool checked)
{
    ui->messagetype_pick->setEnabled(checked);
}

std::pair<QDateTime, QDateTime> MainWindow::getTimeRange() {
    QDateTime start = ui->startTimeEdit->dateTime();
    QDateTime end = ui->endTimeEdit->dateTime();
    return std::make_pair(start, end);
}


void MainWindow::on_saveButton_clicked()
{
    QMessageBox* typeselector = new QMessageBox();
    typeselector->addButton("Save as text", QMessageBox::YesRole);
    typeselector->addButton("Save as image", QMessageBox::AcceptRole);
    //Asks user input
    int imageornormal = typeselector->exec();
    QInputDialog window;
    int closedOrNot =window.exec();
    placeholdername = window.textValue();
    //Verifies user input
    if(ui->CompareDropdown->findText(placeholdername) != -1 & closedOrNot !=0) {
        QMessageBox::warning(this, "Error", "Name already used, delete previous one or use another name");
        return;
    }
    else if (closedOrNot == 1)
    {emit saveButtonClicked(imageornormal);
        ui->CompareDropdown->addItem(placeholdername);}
}


void MainWindow::on_CompareDropdown_activated(int index)
{
    fileCreator* creator_ = new fileCreator;
    ui->horizontalLayout_5->removeWidget(chartview2);
     chartview2 = new QChartView();
    ui->horizontalLayout_5->removeWidget(imagelabel);
     imagelabel = new QLabel();
    placeholdername = ui->CompareDropdown->currentText();
    QList<QString> emptylist = {};
    //If graph was saved as an image it copies it here
    if(creator_->getImageNames(emptylist).contains(placeholdername)) {

        //Removes the old widget (non-image chart) and adds a new one
        ui->horizontalLayout_5->addWidget(imagelabel);
        //Re-initializes the removed widget so it can be added again later
            QPixmap pixmap("graphImages/" + placeholdername + ".png");

          imagelabel->setPixmap(pixmap);

    }
    else{
        ui->horizontalLayout_5->addWidget(chartview2);
    emit compareDropdownActivated();
    }
}

void MainWindow::updateCurrentButton()
{
    ui->GraphcomboBox->setEnabled(1);
    if (ui->roadmaintenance->isChecked()) {
        currentButton_ = Button::RoadMaintenance;
        preferenceButton_ = ui->roadmaintenance->objectName();
    } else if (ui->roadcondition->isChecked()) {
        ui->GraphcomboBox->setEnabled(0);
        currentButton_ = Button::OverallRoadCondition;
        preferenceButton_ = ui->roadcondition->objectName();
    } else if (ui->averageTemperature->isChecked()) {
        currentButton_ = Button::AverageTemperature;
        preferenceButton_ = ui->averageTemperature->objectName();
    } else if (ui->maximumTemperature->isChecked()) {
        currentButton_ = Button::MaximumTemperature;
        preferenceButton_ = ui->maximumTemperature->objectName();
    } else if (ui->minimumTemperature->isChecked()) {
        currentButton_ = Button::MinimumTemperature;
        preferenceButton_ = ui->minimumTemperature->objectName();
    } else if (ui->predictedtemperature->isChecked()) {
        currentButton_ = Button::PredictedTemperature;
        preferenceButton_ = ui->predictedtemperature->objectName();
    } else if (ui->predictedwind->isChecked()) {
        currentButton_ = Button::PredictedWind;
        preferenceButton_ = ui->predictedwind->objectName();
    } else if (ui->observedwind->isChecked()) {
        currentButton_ = Button::ObservedWind;
        preferenceButton_ = ui->observedwind->objectName();
    } else if (ui->observedcloudiness->isChecked()) {
        currentButton_ = Button::ObservedCloudiness;
        preferenceButton_ = ui->observedcloudiness->objectName();
    } else if (ui->precipitation->isChecked()) {
        currentButton_ = Button::Precipitation;
        preferenceButton_ = ui->precipitation->objectName();
    } else if (ui->temperature_f->isChecked()) {
        currentButton_ = Button::TemperatureForecast;
        preferenceButton_ = ui->temperature_f->objectName();
    } else if (ui->temperature_h->isChecked()) {
        currentButton_ = Button::TemperatureHistory;
        preferenceButton_ = ui->temperature_h->objectName();
    } else if (ui->trafficmessages->isChecked()) {
        ui->GraphcomboBox->setEnabled(0);
        currentButton_ = Button::TrafficMessages;
        preferenceButton_ = ui->trafficmessages->objectName();
    } else {
        currentButton_ = Button::NaB;
        preferenceButton_ = "";
    }

    ui->fHoursSelect->setEnabled(currentButton_ == Button::Precipitation || currentButton_ == Button::OverallRoadCondition);
    ui->startTimeEdit->setEnabled(currentButton_ != Button::Precipitation && currentButton_ != Button::OverallRoadCondition && currentButton_ != Button::TrafficMessages && currentButton_ != Button::TemperatureHistory && currentButton_ != Button::ObservedCloudiness && currentButton_ != Button::ObservedWind);
    ui->endTimeEdit->setEnabled(currentButton_ != Button::Precipitation && currentButton_ != Button::OverallRoadCondition && currentButton_ != Button::TrafficMessages && currentButton_ != Button::TemperatureHistory && currentButton_ != Button::ObservedCloudiness && currentButton_ != Button::ObservedWind);
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
    QList<QString> graphs = temp->loadNames();

   for(auto i : graphs) {
       ui->CompareDropdown->addItem(i);
   }

}

//loads previously saved preferences and adds them to the PreferenceDropdown
void MainWindow::loadPreferences() {
    ui->preference_dropdown->clear();
    ui->preference_dropdown->addItem("");
    fileCreator* temp = new fileCreator;
    QList<QString> preferences = temp->loadNames(1);

   for(auto i : preferences) {
       ui->preference_dropdown->addItem(i);
   }
}

MainWindow::Button MainWindow::getCurrentButton()
{
    return currentButton_;
}

std::string MainWindow::getCurrentTask()
{
    int currentIndex = ui->type_pick->currentIndex();
    return tasks[currentIndex].at("id");
}

std::string MainWindow::getCurrentMessage()
{
    int currentIndex = ui->messagetype_pick->currentIndex();
    return messages[currentIndex].at("id");
}

std::string MainWindow::getLocation()
{
    return ui->road_dropdown->currentText().toStdString();
}

QString MainWindow::getForecast()
{
    return ui->fHoursSelect->currentText();
}

//Changes the graphtype based on input and draws the graph again
void MainWindow::on_GraphcomboBox_activated(int index)
{
    if(index == 0){graphtype = "line";}
    else if(index == 1){graphtype = "bar";}
    else if (index == 2) {graphtype = "scatter";}
    emit graphButtonClicked();
}



void MainWindow::on_savePreferenceButton_clicked()
{
    QInputDialog window;
    //Asks and verifies user input
    int closedOrNot = window.exec();
    preferenceName = window.textValue();
    if(ui->preference_dropdown->findText(preferenceName) != -1 & closedOrNot !=0) {
        QMessageBox::warning(this, "Error", "Name already used, delete previous one or use another name");
        return;
    }
    else if (closedOrNot == 1){
        emit PreferenceButtonClicked(ui->road_dropdown->currentIndex(), ui->GraphcomboBox->currentIndex(), ui->type_pick->currentIndex(), ui->fHoursSelect->currentIndex(), ui->messagetype_pick->currentIndex());
    }
}


void MainWindow::on_preference_dropdown_activated(int index)
{
    preferenceName = ui->preference_dropdown->currentText();
    if(preferenceName == ""){return;}
    else{
    fileCreator* creator_ = new fileCreator;
    QJsonObject preference = creator_->getGraphsfromfile(1)[preferenceName].toObject();
    //Reads the state from the file and changes the window to match it
    ui->fHoursSelect->setCurrentIndex(preference["fhours"].toInt());
    ui->type_pick->setCurrentIndex(preference["type_pick"].toInt());
    ui->GraphcomboBox->setCurrentIndex(preference["graphtype"].toInt());
    ui->road_dropdown->setCurrentIndex(preference["location"].toInt());
    ui->messagetype_pick->setCurrentIndex(preference["messagetype"].toInt());
    QRadioButton* button = findChild<QRadioButton*>(preference["radiobutton"].toString());
    button->setChecked(1);
    ui->startTimeEdit->setDateTime(QDateTime::fromString(preference["dates"].toObject()["startdate"].toString()));
    ui->endTimeEdit->setDateTime(QDateTime::fromString(preference["dates"].toObject()["enddate"].toString()));
    ui->GraphcomboBox->setCurrentIndex(preference["graphtype"].toInt());
    updateCurrentButton();
    emit graphButtonClicked();
    }
}


void MainWindow::on_deletePreferenceButton_clicked()
{
    preferenceName = ui->preference_dropdown->currentText();
    emit deletePreferenceButtonClicked();
}

