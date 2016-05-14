#ifndef ENERGYSELECTION_H
#define ENERGYSELECTION_H

#include <QDialog>
#include <QString>

namespace Ui {
class EnergySelection;
}

class EnergySelection : public QDialog
{
    Q_OBJECT

public:
    explicit EnergySelection(QWidget *parent = 0);
    ~EnergySelection();

    float returnEnergy();

private:
    Ui::EnergySelection *ui;

private slots:
    void updateEnergyValue();
};

#endif // ENERGYSELECTION_H
