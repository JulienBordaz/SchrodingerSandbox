#include "newsimdialog.h"
#include "ui_newsimdialog.h"

NewSimDialog::NewSimDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSimDialog)
{
    ui->setupUi(this);
    connect(this->ui->tunnelButton, SIGNAL(clicked()) ,this, SLOT(simuSelected()));
    connect(this->ui->splitButton, SIGNAL(clicked()) ,this, SLOT(simuSelected()));
    connect(this->ui->resonButton, SIGNAL(clicked()) ,this, SLOT(simuSelected()));
    connect(this->ui->emptyButton, SIGNAL(clicked()) ,this, SLOT(simuSelected()));

    setWindowTitle(tr("New simulation"));

    this->ui->simuDescLabel->setText("This simulates the propagation of a wave packet through a potential barrier. Depending on the energy of the particle, a part of the wave can cross the barrier. This effect is known as quantum tunneling.");
}

NewSimDialog::~NewSimDialog()
{
    delete ui;
}

void NewSimDialog::simuSelected()
{
    if (this->ui->tunnelButton->isChecked()) this->ui->simuDescLabel->setText("This simulates the propagation of a wave packet through a potential barrier. Depending on the energy of the particle, a part of the wave can cross the barrier. This effect is known as quantum tunneling.");
    if (this->ui->splitButton->isChecked()) this->ui->simuDescLabel->setText("In this experiment the particle propagates through two close holes in a high potential barrier and interfere with itself.");
    if (this->ui->resonButton->isChecked()) this->ui->simuDescLabel->setText("If several potential barriers are placed successively on the particle way, in certain condition the reflected waves can interfere with each others.");
    if (this->ui->emptyButton->isChecked()) this->ui->simuDescLabel->setText("Sandbox mode. Place the potential barriers you want, choose the particle properties, and run the experiment !");
}


int NewSimDialog::getOption()
{
    if (this->ui->tunnelButton->isChecked()) return 0;
    if (this->ui->splitButton->isChecked()) return 1;
    if (this->ui->resonButton->isChecked()) return 2;
    if (this->ui->emptyButton->isChecked()) return 3;
    return 0;
}
