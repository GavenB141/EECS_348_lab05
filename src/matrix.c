#include <stdio.h>

#define SIZE 5

/**
 * Using a struct allows functions to both accept and return
 * stack-allocated matrices.
 */
typedef struct {
  int items[SIZE][SIZE];
} Matrix;

/**
 * Returns the sum of two matrices. 
 */
Matrix addMatrices(Matrix m1, Matrix m2) {
  Matrix sum;
  
  for(int i = 0; i < SIZE; i++) {
    for(int j = 0; j < SIZE; j++) {
      sum.items[i][j] = m1.items[i][j] + m2.items[i][j];
    }
  }

  return sum;
}

/**
 * Prints the given matrix to stdout.
 */
void printMatrix(Matrix m) {
  for(int i = 0; i < SIZE; i++) {
    printf("| ");
    for(int j = 0; j < SIZE; j++) {
      printf("%4d ", m.items[i][j]);
    }
    printf("|\n");
  }
  printf("\n");
}

int main () {
  Matrix m1 = { .items = {
    {1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10},
    {11, 12, 13, 14, 15},
    {16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25}
  }};
  Matrix m2 = { .items = {
    {25, 24, 23, 22, 21},
    {20, 19, 18, 17, 16},
    {15, 14, 13, 12, 11},
    {10, 9, 8, 7, 6},
    {5, 4, 3, 2, 1}
  }};

  printf("Matrix m1:\n");
  printMatrix(m1);
  printf("Matrix m2:\n");
  printMatrix(m2);

  Matrix sum = addMatrices(m1, m2);
  printf("m1 + m2:\n");
  printMatrix(sum);

  return 0;
}
