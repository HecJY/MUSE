#include <math.h>
#include <stdlib.h>
#include "freq.h"
#include <stdio.h>


int *waveform_gen(int key_index);



int *waveform_gen(key_index){
	int n = 50;
	int waveform[50];
	float freq = freqtable[key_index];
	for(int i; i< n; i++){
		float point = sin(i*2*M_PI*freq);
		waveform[i] = (int) point;
	}

	return waveform;

}

int main () {
	int waveform1 = waveform_gen(1);
	int loop;
	for(loop = 0; loop < 10; loop++){

	   printf("%d ", waveform1[loop]);
	}
	return 0;


}
