/*	Parts of this code have been taken from :
    Quantum Minigolf, a computer game illustrating quantum mechanics
    Copyright (C) 2007 Friedemann Reinhard <friedemann.reinhard@gmail.com> */

#include "quantumwave.h"

QuantumWave::QuantumWave()
{
    psi = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*640*320);
    psik = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*640*320);
    propk = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*640*320);
    propx = (fftw_complex *)fftw_malloc(sizeof(fftw_complex)*640*320);

    fft_psi = fftw_plan_dft_2d(640, 320, psi, psik, FFTW_FORWARD, FFTW_MEASURE);
    fft_psik = fftw_plan_dft_2d(640, 320, psik, psi, FFTW_BACKWARD, FFTW_MEASURE);

    this->deltat=0.000020;

    this->potDistr=new PotentialDistribution();
    this->potDistr->zeroPotential();

    this->initiatePropk();
    this->initiatePropx();


}

void QuantumWave::propagate()
{
    volatile float tre, tim, pre, pim; // swap register and propagator real and imaginary parts
    volatile int x, y;

    for(x=0; x<640; x++){
            for(y=0; y<320; y++){
                tre = psi[x*320+y][0];
                tim = psi[x*320+y][1];

                pre = propx[x*320+y][0];
                pim = propx[x*320+y][1];

                if(pre == 0 && pim == 0){
                    psi[x*320+y][0] = 0;
                    psi[x*320+y][1] = 0;
                }
                else{
                    //propagate the wavefunction.
                    // and correct for last time's shrink and the
                    // FFT's scaling
                    psi[x*320+y][0] = tre*pre - tim*pim;
                    psi[x*320+y][1] = tim*pre + tre*pim;
                }
            }
        }

    // MOMENTUM
    fftw_execute(fft_psi);



        // propagate in momentum space

        for(x=0; x<640; x++){
        for(y=0; y<320; y++){
            tre = psik[x*320+y][0];
            tim = psik[x*320+y][1];
            pre = propk[x*320+y][0];
            pim = propk[x*320+y][1];

            psik[x*320+y][0] = tre*pre - tim*pim;
            psik[x*320+y][1] = tre*pim + tim*pre;
        }
        }

    fftw_execute(fft_psik);
    for (int i=0;i<640;i++)
        for (int j=0;j<320;j++)
        {
            psi[i*320+j][0]/=(640*320);
            psi[i*320+j][1]/=(640*320);
        }
}


void QuantumWave::initiateWavePacket(float rx, float ry, float mu, float sigma, float kx, float ky)
{
    int xcorr, ycorr;
    for (int x=0;x<640;x++)
    {
        xcorr=x-rx;
        for (int y=0;y<320;y++)
        {
            ycorr=y-ry;
            float realtemp=mu*exp(-(pow((xcorr),2)+pow((ycorr),2))/(2*sigma*sigma))*cos(kx*xcorr+ky*ycorr);
            float imtemp=mu*exp(-(pow((xcorr),2)+pow((ycorr),2))/(2*sigma*sigma))*sin(kx*xcorr+ky*ycorr);
            psi[x*320+y][0]=realtemp;
            psi[x*320+y][1]=imtemp;
        }
    }
    this->deltat=10;
    this->deltax=1;
    this->deltay=1;

}

void QuantumWave::initiateWavePacket(SimulationSettings simulationSettings)
{
    this->potDistr=simulationSettings.potDistr;
    int xcorr, ycorr;
    for (int x=0;x<640;x++)
    {
        xcorr=x-simulationSettings.getRx();
        for (int y=0;y<320;y++)
        {
            ycorr=y-simulationSettings.getRy();
            float realtemp=simulationSettings.getMu()*exp(-(pow((xcorr),2)+pow((ycorr),2))/(2*simulationSettings.getSigma()*simulationSettings.getSigma()))*cos(simulationSettings.getKx()*xcorr+simulationSettings.getKy()*ycorr);
            float imtemp=simulationSettings.getMu()*exp(-(pow((xcorr),2)+pow((ycorr),2))/(2*simulationSettings.getSigma()*simulationSettings.getSigma()))*sin(simulationSettings.getKx()*xcorr+simulationSettings.getKy()*ycorr);
            psi[x*320+y][0]=realtemp;
            psi[x*320+y][1]=imtemp;
        }
    }
    this->deltat=simulationSettings.getDeltat();
    this->deltax=simulationSettings.getDeltax();
    this->deltay=simulationSettings.getDeltay();

}

void QuantumWave::initiatePropk()
{
    int x, y;
        float yscale = 640/320*640/320; // scale factor to compensate for different
                                                  // k_0 in x and y direction due to different dimensions

        for(x=0; x<640/2; x++){         
            for(y=0; y<320/2; y++){
                propk[x*320+y][0] = cos(deltat*(-x*x - yscale*y*y));
                propk[x*320+y][1] = sin(deltat*(-x*x - yscale*y*y));
            }
            for(y=320/2; y<320; y++){
                propk[x*320+y][0] = cos(deltat*(-x*x - yscale*(y-320)*(y-320)));
                propk[x*320+y][1] = sin(deltat*(-x*x - yscale*(y-320)*(y-320)));
            }
        }
        for(x=640/2; x<640; x++){
            for(y=0; y<320/2; y++){
                propk[x*320+y][0] = cos(deltat*(-(x-640)*(x-640) - yscale*y*y));
                propk[x*320+y][1] = sin(deltat*(-(x-640)*(x-640) - yscale*y*y));
            }
            for(y=320/2; y<320; y++){
                propk[x*320+y][0] = cos(deltat*(-(x-640)*(x-640) - yscale*(y-320)*(y-320)));
                propk[x*320+y][1] = sin(deltat*(-(x-640)*(x-640) - yscale*(y-320)*(y-320)));
            }
        }
}

void QuantumWave::initiatePropx()
{
    int x, y;

        // extract the potential
        for(x=0; x<640; x++){
        for(y=0; y<320; y++){

            propx[x*320+y][0] = cos(-.5*this->potDistr->getPotential(x,y)*deltat*30000/255);
            propx[x*320+y][1] = sin(-.5*this->potDistr->getPotential(x,y)*deltat*30000/255);
            }
        }

}


float QuantumWave::returnSquarePot(int x,int y)
{
    return sqrt(psi[x*320+y][0]*psi[x*320+y][0]+psi[x*320+y][1]*psi[x*320+y][1]);
}

float QuantumWave::returnReal(int x,int y)
{
    return sqrt(psi[x*320+y][0]*psi[x*320+y][0]);
}

float QuantumWave::returnIm(int x,int y)
{
    return sqrt(psi[x*320+y][1]*psi[x*320+y][1]);
}

float QuantumWave::returnSquarePotk(int x,int y)
{
    return sqrt(psik[x*320+y][0]*psik[x*320+y][0]+psik[x*320+y][1]*psik[x*320+y][1]);
}

PotentialDistribution *QuantumWave::getPotentialDistribution()
{
    return (this->potDistr);
}
