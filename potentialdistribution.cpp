#include "potentialdistribution.h"

PotentialDistribution::PotentialDistribution()
{
   nRect=0;
    //rectanglePotList = new QList<float[6]>();
}

void PotentialDistribution::zeroPotential()
{
    for (int i=0;i<640;i++)
        for (int j=0;j<320;j++)
        {
            this->Potential[i][j]=0;
        }

    this->rectanglePotList.clear();
    nRect=0;
}

float PotentialDistribution::getPotential(int x, int y)
{
    return this->Potential[x][y];
}

void PotentialDistribution::setRectangle(int xmin, int xmax, int ymin, int ymax, float pot)
{
    if (xmin<0) xmin = 0;
    if (xmax>639) xmax = 639;
    if (ymin<0) ymin = 0;
    if (ymax>320) ymax = 320;

    for (int i=xmin; i<=xmax; i++)
        for (int j=320-ymax; j<=320-ymin; j++)
            this->Potential[i][j]+=pot;

    // adding info to the rectangle datas - for faster drawing (not pixel one by one)
    QVector<float> rectangleTemp(6);
    rectangleTemp[0]=1;
    rectangleTemp[1]=xmin;
    rectangleTemp[2]=xmax;
    rectangleTemp[3]=ymin;
    rectangleTemp[4]=ymax;
    rectangleTemp[5]=pot;

    rectanglePotList.push_back(rectangleTemp);

    this->nRect++;
}

int PotentialDistribution::isOnRectangle(int x, int y, int ignored)
{
    if (this->nRect == 0) return false;
    for (int n=0;n<rectanglePotList.length();n++)
    {
        QVector<float> rectanglePotTemp = rectanglePotList.at(n);
        if (n != ignored && x >= rectanglePotTemp[1] && x <= rectanglePotTemp[2] && y >=rectanglePotTemp[3] && y <= rectanglePotTemp[4]) return n;
    }
    return -1;
}

void PotentialDistribution::removePotentialData(int n)
{
    rectanglePotList.removeAt(n);
    this->updatePotentialFromAllDatas();
}

void PotentialDistribution::updatePotentialFromData(int n)
{

}

void PotentialDistribution::updatePotentialFromAllDatas()
{
    for (int i=0;i<640;i++)
        for (int j=0;j<320;j++)
        {
            this->Potential[i][j]=0;
        }

    for (int n=0;n<rectanglePotList.length();n++)
    {
        QVector<float> rectanglePotTemp = rectanglePotList.at(n);
        for (int i=rectanglePotTemp[1]; i<= rectanglePotTemp[2]; i++)
            for (int j=320-rectanglePotTemp[4]; j<=320-rectanglePotTemp[3]; j++)
                this->Potential[i][j]+=rectanglePotTemp[5];
    }
}
void PotentialDistribution::addRectangleData(int xmin, int xmax, int ymin, int ymax, float pot)
{
    if (xmin<0) xmin = 0;
    if (xmax>639) xmax = 639;
    if (ymin<0) ymin = 0;
    if (ymax>320) ymax = 320;

    // adding info to the rectangle datas - for faster drawing (not pixel one by one)
    QVector<float> rectangleTemp(6);
    rectangleTemp[0]=1;
    rectangleTemp[1]=xmin;
    rectangleTemp[2]=xmax;
    rectangleTemp[3]=ymin;
    rectangleTemp[4]=ymax;
    rectangleTemp[5]=pot;

    rectanglePotList.append(rectangleTemp);

}
