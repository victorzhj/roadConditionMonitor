#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->road_dropdown, &QComboBox::currentIndexChanged,
            this, &MainWindow::road);
    ui->horizontalLayout->addWidget(chartview);
    ui->horizontalLayout_5->addWidget(chartview2);

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

void MainWindow::drawGraph(model* model_, bool WhichGraph)
{
    QChartView* tempchartview;
    QList<QPoint> pointdata;
    if(WhichGraph){tempchartview = chartview; pointdata = model_->getChart();}
    else {tempchartview = chartview2; pointdata = model_->pointdata2_;}
    CreateGraph *graph = new CreateGraph();
    QLineSeries* series = new QLineSeries();
    for (auto& point : pointdata) {
            series->append(point);
        }

    graph->drawGraph(series, tempchartview);
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
<<<<<<< HEAD
    placeholdername = QInputDialog::getText(this, "Input required!","Enter graph name:");
    emit saveButtonClicked();
}
=======
    placeholdername = QInputDialog::getText(this, "Input required","Enter graph name:");
>>>>>>> 60c564cdb59eada3f0067c5767cefe5bfaae2d6d

    if(ui->CompareDropdown->findText(placeholdername) != -1) {
        QMessageBox::warning(this, "Error", "Name already used, delete previous one or use another name");
        return;
    }
    else{emit saveButtonClicked();ui->CompareDropdown->addItem(placeholdername);}
}


void MainWindow::on_CompareDropdown_activated(int index)
{
    placeholdername = ui->CompareDropdown->currentText();
    emit compareDropdownActivated();
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
