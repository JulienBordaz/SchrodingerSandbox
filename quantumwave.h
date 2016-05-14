/*	Parts of this code have been taken from :
    Quantum Minigolf, a computer game illustrating quantum mechanics
    Copyright (C) 2007 Friedemann Reinhard <friedemann.reinhard@gmail.com> */

#ifndef QUANTUMWAVE_H
#define QUANTUMWAVE_H

# include <cmath>
#include <fftw3.h>
#include "potentialdistribution.h"
#include <simulationsettings.h>

class QuantumWave
{

    fftw_plan fft_psi;
    fftw_plan fft_psik;

    // time/space steps
    float deltat;
    float deltax;
    float deltay;

    public:
    // wave function and propagator
    fftw_complex *psi;
    fftw_complex *psik;
    fftw_complex *propk;
    fftw_complex *propx;

    PotentialDistribution *potDistr;

    QuantumWave();
    void propagate();
    void initiateWavePacket(float rx, float ry, float mu, float sigma, float kx, float ky);
    void initiateWavePacket(SimulationSettings simulationSettings);
    void initiatePropk();
    void initiatePropx();
    float returnSquarePot(int x,int y);
    float returnReal(int x,int y);
    float returnIm(int x,int y);
    float returnSquarePotk(int x,int y);

    PotentialDistribution* getPotentialDistribution();

};

#endif // QUANTUMWAVE_H
