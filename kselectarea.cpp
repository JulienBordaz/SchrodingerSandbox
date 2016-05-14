#include "KSelectArea.h"

/*
 * The area where the direction of the wave can be changed.
 *
*/

KSelectArea::KSelectArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    this->kSelectIsActive=1;
    this->kx=1;
    this->ky=0;
}

QSize KSelectArea::minimumSizeHint() const
{
    return QSize(80,80);
}

QSize KSelectArea::sizeHint() const
{
    return QSize(80, 80);
}


void KSelectArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    if (kSelectIsActive == 1)
    {
        painter.setOpacity(1);
    } else
    {
        painter.setOpacity(0.7);
    }
    QPoint coord1 = QPoint(40,40);
    QPoint coord2 = QPoint(40+39*kx,40-39*ky);
    painter.drawLine(coord1,coord2);
    painter.drawEllipse(coord1,39,39);
}

void KSelectArea::clicDetected(QPoint coord)
{
    if (kSelectIsActive == 1)
    {
        this->repaint();
        float x=coord.x()-40-20;
        float y=-coord.y()+62+240;
        float norm=sqrt(x*x+y*y);
        this->kx=x/norm;
        this->ky=y/norm;
        this->repaint();
    }
}

float KSelectArea::getkx()
{
    return kx;
}

float KSelectArea::getky()
{
    return ky;
}

void KSelectArea::setkx(float kx)
{
    this->kx = kx;
}

void KSelectArea::setky(float ky)
{
    this->ky = ky;
}

void KSelectArea::setkSelectActive()
{
    this->kSelectIsActive=1;
    this->repaint();
}

void KSelectArea::setkSelectInactive()
{
    this->kSelectIsActive=0;
    this->repaint();
}
