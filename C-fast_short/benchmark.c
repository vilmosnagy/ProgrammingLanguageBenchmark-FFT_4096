#include <time.h>
#include <stdio.h>
#include "fft.h"

#define SIZE (1<<LOG2FFTSIZE)

struct _sample xy[SIZE];
struct _sample xy_out[SIZE];

int main() {
    int i;
    double eltime;
    struct timespec gstart, gend;

    for(i=0; i<SIZE/2; i++) { xy[i].i= 1.*(1U<<INTMULSAMPLE); xy[i].q=0; }
    for(   ; i<SIZE  ; i++) { xy[i].i=-1.*(1U<<INTMULSAMPLE); xy[i].q=0; }

// FFT
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (i=0; i<FFT_REPEAT; i++) fft(LOG2FFTSIZE, xy_out, xy);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);

    eltime = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;
    printf("\n%6d piece(s) of %d pt FFT;  %9.5f ms/piece\n", FFT_REPEAT, 1<<LOG2FFTSIZE, eltime/FFT_REPEAT);

    for(i=0; i<6; i++) {
	printf("%3d %16.3f %16.3f\n", i, (double)xy_out[i].i/(1U<<INTMULSAMPLE), (double)xy_out[i].q/(1U<<INTMULSAMPLE));
    }
    return 0;
}
