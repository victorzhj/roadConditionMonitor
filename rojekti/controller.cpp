#include "controller.h"

controller::controller(model* model, MainWindow* view, QObject *parent) : QObject(parent)
  , model_(model)
  , view_(view)
{
    updateGraph();
    model->jsonGetData();
}

void controller::updateGraph() {
    view_->drawGraph(model_);
}

void controller::getData() {
   model_->jsonGetData();
}
