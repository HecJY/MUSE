#include <stdio.h>
#include <math.h>
#define N 1024
int main(void) {
 int x;
 printf("const short int wavetable[%d] = {\n", N);
 for(x=0; x<N; x++) {
 int value = 32767 * sin(2 * M_PI * x / N);
 printf("%d, ", value);
 if ((x % 8) == 7) printf("\n");
 }
 printf("};\n");
}
