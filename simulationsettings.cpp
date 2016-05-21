#include "simulationsettings.h"

SimulationSettings::SimulationSettings()
{
    this->kx=1;
    this->ky=1;
    this->rx=1;
    this->ry=1;
    this->mu=1;
    this->sigma=1;
    this->deltat=1;
    this->deltax=1;
    this->deltay=1;
    this->potDistr=new PotentialDistribution();
    this->potDistr->zeroPotential();
}
SimulationSettings::SimulationSettings(float kx, float ky, float rx, float ry, float mu, float sigma, float deltat, float deltax, float deltay)
{
    this->kx=kx;
    this->ky=ky;
    this->rx=rx;
    this->ry=ry;
    this->mu=mu;
    this->sigma=sigma;
    this->deltat=deltat;
    this->deltax=deltax;
    this->deltay=deltay;
    this->potDistr=new PotentialDistribution();
    this->potDistr->zeroPotential();
}

SimulationSettings::~SimulationSettings()
{

}

SimulationSettings::SimulationSettings(const SimulationSettings &copie)
{
    this->kx=copie.kx;
    this->ky=copie.ky;
    this->rx=copie.rx;
    this->ry=copie.ry;
    this->mu=copie.mu;
    this->sigma=copie.sigma;
    this->deltat=copie.deltat;
    this->deltax=copie.deltax;
    this->deltay=copie.deltay;
    this->potDistr=new PotentialDistribution();
    this->potDistr=copie.potDistr;
}

QDataStream & operator << (QDataStream & out, const SimulationSettings & simulationSettings)

{

    out << simulationSettings.kx
        << -simulationSettings.ky
        << simulationSettings.rx
        << simulationSettings.ry
        << simulationSettings.mu
        << simulationSettings.sigma
        << simulationSettings.deltat
        << simulationSettings.deltax
        << simulationSettings.deltay;
    out << simulationSettings.potDistr->rectanglePotList.length();
    for (int i=0;i<simulationSettings.potDistr->rectanglePotList.length();i++)
        for (int j=0;j<6;j++)
            out << simulationSettings.potDistr->rectanglePotList.at(i)[j];


    return out;

}

QDataStream & operator >> (QDataStream & in, SimulationSettings & simulationSettings)

{

    in >> simulationSettings.kx;
    in >> simulationSettings.ky;
    in >> simulationSettings.rx;
    in >> simulationSettings.ry;
    in >> simulationSettings.mu;
    in >> simulationSettings.sigma;
    in >> simulationSettings.deltat;
    in >> simulationSettings.deltax;
    in >> simulationSettings.deltay;

    QList<QVector <float> > rectanglePotListTemp;

    simulationSettings.potDistr->zeroPotential();
    in >> simulationSettings.potDistr->nRect;

    for (int i=0;i<simulationSettings.potDistr->nRect;i++)
    {
        QVector<float> rectangleTemp(6);
        for (int j=0;j<6;j++)
        {
            in >> rectangleTemp[j];
        }
        rectanglePotListTemp.append(rectangleTemp);
    }
    simulationSettings.potDistr->rectanglePotList=rectanglePotListTemp;

    return in;

}

void SimulationSettings::initSimulationSettingsSystem()
{
    qRegisterMetaTypeStreamOperators<SimulationSettings>("SimulationSettings");
    qMetaTypeId<SimulationSettings>();             // Teste la validité de la classe Contact
}
