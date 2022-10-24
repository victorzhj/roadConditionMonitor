#include "controller.h"

controller::controller(model* model, MainWindow* view, QObject *parent) : QObject(parent)
  , model_(model)
  , view_(view)
{
    updateGraph();
}

void controller::updateGraph() {
    view_->drawGraph(model_);
}
