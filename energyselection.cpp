#include "energyselection.h"
#include "ui_energyselection.h"

EnergySelection::EnergySelection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnergySelection)
{
    ui->setupUi(this);
    connect(this->ui->energySlider, SIGNAL(sliderMoved(int)) ,this, SLOT(updateEnergyValue()));
}

EnergySelection::~EnergySelection()
{
    delete ui;
}

float EnergySelection::returnEnergy()
{
    return (float) this->ui->energySlider->sliderPosition()/500;
}

void EnergySelection::updateEnergyValue(){
    double sliderPos = (double) this->ui->energySlider->sliderPosition();
    QString energyString;
    energyString.setNum(sliderPos/500);
    this->ui->energyValueLabel->setText(energyString);
}
