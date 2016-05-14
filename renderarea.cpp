#include "renderarea.h"

/*
 * The main area where the wave and the potentials are displayed.
 *
 */

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    this->setIsDrawingRectangle(false);
    this->setSelectedRectangle(-1);

}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(640, 320);
}

QSize RenderArea::sizeHint() const
{
    return QSize(640, 320);
}


void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    // drawing the wave
    for (int i=1;i<640;i++)
        for (int j=1;j<320;j++)
        {
           if (this->gridnew[i][j]>0.01)
            {
                painter.setOpacity(this->gridnew[i][j]);
                painter.drawPoint(i,j);
            }
        }

    // drawing the potential rectangles
    for (int k=0;k<rectanglePotList.length();k++)
    {
        painter.setOpacity(0.5);
        if (k == this->selectedRectangle) painter.setOpacity(1);

            int rleft=this->rectanglePotList.at(k)[1];
            int rtop=this->rectanglePotList.at(k)[4];
            int rwidth=this->rectanglePotList.at(k)[2]-this->rectanglePotList.at(k)[1];
            int rheight=this->rectanglePotList.at(k)[4]-this->rectanglePotList.at(k)[3];
            QRect rect = QRect(rleft, 320-rtop, rwidth, rheight);
            painter.drawRect(rect);

    }

    // drawing (eventually) the potential being draw
    if (this->isDrawingRectangle)
    {
        QRect rect2 = QRect(coord1,coord2);
        painter.drawRect(rect2);
    }

}

void RenderArea::updateGrid(int i, int j, float value)
{
   this->gridnew[i][j]=value;
}

void RenderArea::updateRectPot(float RectPot[6][10])
{
    for (int i=0;i<6;i++)
        for (int j=0;j<10;j++)
            this->RectanglePot[i][j]=RectPot[i][j];
}

void RenderArea::updateRectPotList(QList<QVector <float> > rectanglePotList)
{
   this->rectanglePotList=rectanglePotList;
}

void RenderArea::setIsDrawingRectangle(bool isDrawing)
{
    this->isDrawingRectangle=isDrawing;
}

void RenderArea::setCoord1(QPoint coord1)
{
    this->coord1=coord1;
}

void RenderArea::setCoord2(QPoint coord2)
{
    this->coord2=coord2;
}

void RenderArea::setSelectedRectangle(int n)
{
    this->selectedRectangle=n;
}

int RenderArea::getSelectedRectangle()
{
    return this->selectedRectangle;
}
