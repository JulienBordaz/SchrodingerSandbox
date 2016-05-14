#ifndef NEWSIMDIALOG_H
#define NEWSIMDIALOG_H

#include <QDialog>

namespace Ui {
class NewSimDialog;
}

class NewSimDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSimDialog(QWidget *parent = 0);
    ~NewSimDialog();
    int getOption();

private:
    Ui::NewSimDialog *ui;

private slots:
    void simuSelected();
};

#endif // NEWSIMDIALOG_H
