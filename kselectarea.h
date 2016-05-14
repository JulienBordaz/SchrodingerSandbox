#ifndef KSELECTAREA_H
#define KSELECTAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QtGui>
#include <QPoint>
#include <math.h>
#include <QMessageBox>

/*
 * The area where the direction of the wave can be changed.
 *
*/

class KSelectArea : public QWidget
{
    Q_OBJECT

private:
    float kx;
    float ky;
    bool kSelectIsActive;

public:
     KSelectArea(QWidget *parent = 0);
     QSize minimumSizeHint() const;
     QSize sizeHint() const;
     float getkx();
     float getky();
     void setkx(float kx);
     void setky(float ky);
     void setkSelectActive();
     void setkSelectInactive();
     void clicDetected(QPoint coord);

 protected:
     void paintEvent(QPaintEvent *event);

};

#endif
