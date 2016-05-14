#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    connect(this->ui->closeButton, SIGNAL(clicked()),this, SLOT(close_butt()));

}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::close_butt()
{
    this->close();
}
