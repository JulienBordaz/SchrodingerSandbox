#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QWidget>
#include <QtGui>
#include <QPoint>

/*
 * The main area where the wave and the potentials are displayed.
 *
 */

class RenderArea : public QWidget
{
    Q_OBJECT
public:
     RenderArea(QWidget *parent = 0);
     QSize minimumSizeHint() const;
     QSize sizeHint() const;

     float gridold[640][320];
     float gridnew[640][320];

     float RectanglePot[6][10];
     QList<QVector <float> > rectanglePotList;

     void updateGrid(int x, int y, float value);
     void updateRectPot(float RectPot[6][10]);
     void updateRectPotList(QList<QVector <float> > rectanglePotList);

     void setCoord1(QPoint coord1);
     void setCoord2(QPoint coord2);

     void setSelectedRectangle(int n);
     int getSelectedRectangle();

     void setIsDrawingRectangle(bool isDrawing);


 protected:
     void paintEvent(QPaintEvent *event);
     int selectedRectangle;

     bool isDrawingRectangle;
     QPoint coord1;
     QPoint coord2;


};

#endif
