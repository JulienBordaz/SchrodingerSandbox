#ifndef POTENTIALDISTRIBUTION_H
#define POTENTIALDISTRIBUTION_H

#include <cmath>
#include <QList>
#include <QVector>

class PotentialDistribution
{
    float Potential[640][320];

public:
    PotentialDistribution();
    void zeroPotential();
    float getPotential(int x, int y);
    void setRectangle(int xmin, int xmax, int ymin, int ymax, float pot);
    void addRectangleData(int xmin, int xmax, int ymin, int ymax, float pot);
    void updatePotentialFromData(int n);
    void updatePotentialFromAllDatas();
    void removePotentialData(int n);

    // 0 : active, 1-4 : xmin, xmax, ymin, ymax, 5 : pot
    QList<QVector <float> > rectanglePotList;
    int nRect;

    int isOnRectangle(int x, int y, int ignored);
};

#endif // POTENTIALDISTRIBUTION_H
