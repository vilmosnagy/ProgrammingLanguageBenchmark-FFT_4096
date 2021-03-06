#include <math.h>
#include "dft.h"

static int dft_point = 0;
static double dft_revpt;

static double complex dft_phasediffXY;
static double complex dft_vfoXY[1<<LOG2FFTSIZE];


void dft_init(int point) {
    dft_point = point;
    dft_revpt = 1./point;
    //phasediffXY = cos(-2*M_PI/point) + I*sin(-2*M_PI/point);
    dft_phasediffXY = cexp(-2j*M_PI/point);

    for (int i=0; i<point; i++) dft_vfoXY[i]=1.;
}

static double complex dft_corr=0;
void dft_sample(double complex *xy_out, double complex xy_sample) {
    xy_sample -= dft_corr*dft_revpt;		// remove oldest value from DFT

    dft_corr = 0;
    double complex phaseXY = 1.;

    for(int i=0; i<dft_point; i++) {
	double complex tmp_vfoXY = dft_vfoXY[i];// register --> faster
	double complex tmp_xy_out = xy_out[i];	// register --> faster

	tmp_xy_out += xy_sample*tmp_vfoXY;	// new DFT value

	tmp_vfoXY *= phaseXY;			// oscillator new state
	phaseXY *= dft_phasediffXY;		// oscillator new speed
	dft_corr += tmp_xy_out*conj(tmp_vfoXY);	// generate new prev. correction
	dft_vfoXY[i]=tmp_vfoXY;
	xy_out[i] = tmp_xy_out;
    }
}
