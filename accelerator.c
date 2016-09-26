#include <stdlib.h>
#include <stdio.h>
#include "accelerator.h"
#include "debug.h"

void simMul(double *A, double *B, double *C, int len){
  DEBUG_PRINT("start simMul\n");
  int i;
  for (i=0; i < len; ++i){
    DEBUG_PRINT ("%f x %f\n", A[i], B[i]);
    C[i] = B[i] * A[i];
  }
}

// I is row, J is column
#define A(I,J) A[(I) + (J)* (numARows)]
#define B(I,J) B[(I) + (J)*(numBRows)]
#define tmpA(I,J) tmpA[(I) + (J)*(numTmpARows)]
#define C(I,J) C[(I) + (J)* (numCRows)]

double summation(double *val, int len){
  double tmp = 0.;
  int i;
  for(i=0; i<len; ++i) {
    tmp+=val[i];
  }
  return tmp;
}

void matrixMultiply(double *A, double *B, double *C,
                    int numARows, int numAColumns,
                    int numBRows, int numBColumns,
                    int numCRows, int numCColumns) {
  DEBUG_PRINT("arow=%d,acol=%d,brow=%d,bcol=%d,crow=%d,ccol=%d\n",numARows,numAColumns,numBRows,numBColumns,numCRows,numCColumns);
  int i,j,k;
  double *tmpA = malloc(sizeof(double) * numARows * numAColumns);
  // transpose B
  int numTmpARows = numAColumns;
  int numTmpAColumns = numARows;
  for (j=0; j<numTmpAColumns; ++j) {
    for (i=0; i<numTmpARows; ++i) {
        tmpA(i,j) = A(j,i);
    }
  }
  DEBUG_PRINT("A:\n");
  for (i=0; i<numARows; ++i) {
    for (j=0; j<numAColumns; ++j) {
      DEBUG_PRINT("%p %f ", &A(i,j), A(i,j));
    }
    DEBUG_PRINT("\n");
  }
  DEBUG_PRINT("\nB:\n");
  for (i=0; i<numBRows; ++i) {
    for (j=0; j<numBColumns; ++j) {
      DEBUG_PRINT("%p %f ", &B(i,j), B(i,j));
    }
    DEBUG_PRINT("\n");
  }
  DEBUG_PRINT("\ntmpA:\n");
  for (i=0; i<numTmpARows; ++i) {
    for (j=0; j<numTmpAColumns; ++j) {
      DEBUG_PRINT("%p %f ", &tmpA(i,j), tmpA(i,j));
    }
    DEBUG_PRINT("\n");
  }
  DEBUG_PRINT("\n");

  double *tmpResult = malloc (sizeof(double) * numTmpARows);
  double *pa = tmpA, *pb = B;
  for(j=0; j<numCColumns; ++j) {
    for(i=0; i<numCRows; ++i) {
      simMul(pa, pb, tmpResult, numTmpARows);
      double sum = summation(tmpResult, numTmpARows);
      C(i,j) = sum;
      pa += numTmpARows;
    }
    pb += numBRows;
    pa = tmpA;
  }
  free(tmpA);
  free(tmpResult);
}
