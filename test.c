/*#### Call BLAS Fortran interface

This example shows calling dgemm Fortran interface in C. https://gist.github.com/xianyi/5780018

```
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "cblas_headers.h"
#include "debug.h"

extern void dgemm_(char*, char*, int*, int*, int*, double*, double*, int*, double*, int*, double*, double*, int*);

int main(int argc, char* argv[])
{
  int i;
  printf("test!\n");
  if(argc<4){
    printf("Input Error\n");
    return 1;
  }

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int k = atoi(argv[3]);
  int sizeofa = m * k;
  int sizeofb = k * n;
  int sizeofc = m * n;
  char ta = 'N';
  char tb = 'N';
  double alpha = 1;
  double beta = 0;

  struct timeval start,finish;
  double duration;

  double* A = (double*)malloc(sizeof(double) * sizeofa);
  double* B = (double*)malloc(sizeof(double) * sizeofb);
  double* C = (double*)malloc(sizeof(double) * sizeofc);

  srand((unsigned)time(NULL));

  DEBUG_PRINT("A=");
  for (i=0; i<sizeofa; i++) {
    A[i] = i%3+1;
    DEBUG_PRINT("%f,", A[i]);
  }
  DEBUG_PRINT("\nB=");
  for (i=0; i<sizeofb; i++) {
    B[i] = i%3+1;
    DEBUG_PRINT("%f,", B[i]);
  }
  DEBUG_PRINT("\nC=");
  for (i=0; i<sizeofc; i++) {
    C[i] = i%3+1;
    DEBUG_PRINT("%f,", C[i]);
  }
  DEBUG_PRINT("\n");

  printf("m=%d,n=%d,k=%d,alpha=%lf,beta=%lf,sizeofc=%d\n",m,n,k,alpha,beta,sizeofc);
  gettimeofday(&start, NULL);
  dgemm_(&ta, &tb, &m, &n, &k, &alpha, A, &m, B, &k, &beta, C, &m);
  gettimeofday(&finish, NULL);

  DEBUG_PRINT("result=");
  for (i=0; i<sizeofc; i++) {
    DEBUG_PRINT("%f,", C[i]);
  }
  DEBUG_PRINT("\n");

  duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;
  double gflops = 2.0 * m *n*k;
  gflops = gflops/duration*1.0e-6;

  FILE *fp;
  fp = fopen("timeDGEMM.txt", "a");
  fprintf(fp, "%dx%dx%d\t%lf s\t%lf MFLOPS\n", m, n, k, duration, gflops);
  printf("%dx%dx%d\tduration:%lf s\t%lf MFLOPS\n", m, n, k, duration, gflops);
  fclose(fp);

  free(A);
  free(B);
  free(C);
  return 0;
}
