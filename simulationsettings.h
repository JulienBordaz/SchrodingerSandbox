#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H

#include <QVariant>

#include <potentialdistribution.h>

class SimulationSettings
{
    public:
    SimulationSettings();
    ~SimulationSettings();
    SimulationSettings (const SimulationSettings & copie);
    SimulationSettings(float kx, float ky, float rx, float ry, float mu, float sigma, float deltat, float deltax, float deltay);
    static void initSimulationSettingsSystem();


    void setKx(float kx) { this->kx = kx; }
    float getKx() { return this->kx; }
    void setKy(float ky) { this->ky = ky; }
    float getKy() { return this->ky; }
    void setRx(float rx) { this->rx = rx; }
    float getRx() { return this->rx; }
    void setRy(float ry) { this->ry = ry; }
    float getRy() { return this->ry; }
    void setMu(float mu) { this->mu = mu; }
    float getMu() { return this->mu; }
    void setSigma(float sigma) { this->sigma = sigma; }
    float getSigma() { return this->sigma; }
    void setDeltat(float deltat) { this->deltat = deltat; }
    float getDeltat() { return this->deltat; }
    void setDeltax(float deltax) { this->deltax = deltax; }
    float getDeltax() { return this->deltax; }
    void setDeltay(float deltay) { this->deltay = deltay; }
    float getDeltay() { return this->deltay; }
    void setPotDistr(PotentialDistribution *potDistr) { this->potDistr = potDistr; }
    PotentialDistribution  * getPotDistr() { return this->potDistr; }

    PotentialDistribution *potDistr;

    private:
    // time/space steps
    float deltat;
    float deltax;
    float deltay;

    float rx;
    float ry;
    float mu;
    float sigma;
    float kx;
    float ky;



    friend QDataStream & operator << (QDataStream &, const SimulationSettings &);
    friend QDataStream & operator >> (QDataStream &, SimulationSettings &);

};

Q_DECLARE_METATYPE(SimulationSettings)
QDataStream & operator << (QDataStream & out, const SimulationSettings & simulationSettings);
QDataStream & operator >> (QDataStream & in, SimulationSettings & simulationSettings);

#endif // SIMULATIONSETTINGS_H
