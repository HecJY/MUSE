#include <math.h>
#include <stdlib.h>
#include "freq.h"
#include <stdio.h>
#define M_PI 3.141592

int waveform[100];
int *waveform_gen(int key_index);


int *waveform_gen(int key_index){
	float offset = 2048.0;
	float amp = 500;
	int n = 100;
	float freq = freqtable[key_index];
	for(int i=0; i< n; i++){
		float point =offset +amp* sin(i*2*M_PI*freq);
		waveform[i] = (int) point;
	}

	return waveform;

}

int main () {
	int *waveform1;
	waveform1 = waveform_gen(1);
	int loop;
	FILE *fp;
	fp = fopen("arrayfile.txt","w");
	
	for(loop = 0; loop < 100; loop++){

	   fprintf(fp,"%d,", waveform1[loop]);
	}
	return 0;


}
