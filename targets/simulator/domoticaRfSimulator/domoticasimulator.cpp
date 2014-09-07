#include "domoticasimulator.h"
#include "ui_domoticasimulator.h"

DomoticaSimulator::DomoticaSimulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DomoticaSimulator)
{
    ui->setupUi(this);
}

DomoticaSimulator::~DomoticaSimulator()
{
    delete ui;
}
