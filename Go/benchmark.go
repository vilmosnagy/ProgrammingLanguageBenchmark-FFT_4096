package main

import (
    "fmt"
    "time"
    "fft"
)

const LOG2FFTSIZE uint= 12
const FFT_REPEAT int = 1000

const SIZE = (1<<LOG2FFTSIZE)
var xy [SIZE]complex128
var xy_out_fft [SIZE]complex128

func main() {
    var i int
    for i=0; i<SIZE/2; i++ { xy[i]= (1.+0i) }
    for    ; i<SIZE  ; i++ { xy[i]= (-1.+0i) }

// FFT
    var startTime = time.Now().UnixNano()
    for i=0; i<FFT_REPEAT; i++ { xy_out_fft = fft.Fft(LOG2FFTSIZE, xy) }
    var endTime = time.Now().UnixNano()

    fmt.Printf("%8d piece(s) of %d pt FFT;    %.3f ms/piece\n\n", FFT_REPEAT, SIZE, float64(endTime-startTime)/float64(1e6)/float64(FFT_REPEAT))

    for i=0; i<6; i++ {
	fmt.Printf("%d %f %f\n", i, real(xy_out_fft[i]), imag(xy_out_fft[i]))
    }
}
