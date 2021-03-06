#include <time.h>
#include <iostream>
#include "fft.h"

#define SIZE (1<<LOG2FFTSIZE)

std::complex<double> xy[SIZE];
std::complex<double> xy_out[SIZE];

int main() {
    int i;
    double eltime;
    struct timespec gstart, gend;

    for(i=0; i<SIZE/2; i++) xy[i]= 1.;
    for(   ; i<SIZE  ; i++) xy[i]=-1.;

// FFT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    fft *ff = new fft();
    for (i=0; i<FFT_REPEAT; i++) ff->calc(LOG2FFTSIZE, xy_out, xy);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime = 1000.*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;
    printf("\n%6d piece(s) of %d pt FFT;  %9.5f ms/piece\n", FFT_REPEAT, 1<<LOG2FFTSIZE, eltime/FFT_REPEAT);

    for(i=0; i<6; i++) {
	printf("%3d %16.9f %16.9f %16.9f\n", i, xy_out[i].real(), xy_out[i].imag(), abs(xy_out[i]));
    }
    return 0;
}
