#include <stdio.h>

#define SIZE 5

/**
 * Prints the given matrix to stdout
 */
void printMatrix(int m[SIZE][SIZE]) {
  for(int i = 0; i < SIZE; i++) {
    printf("| ");
    for(int j = 0; j < SIZE; j++) {
      printf("%4d ", m[i][j]);
    }
    printf("|\n");
  }
}

int main () {
  int m1[SIZE][SIZE] = {
    {1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10},
    {11, 12, 13, 14, 15},
    {16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25}
  };
  int m2[SIZE][SIZE] = {
    {25, 24, 23, 22, 21},
    {20, 19, 18, 17, 16},
    {15, 14, 13, 12, 11},
    {10, 9, 8, 7, 6},
    {5, 4, 3, 2, 1}
  };

  printf("Matrix A:\n");
  printMatrix(m1);
  printf("Matrix B:\n");
  printMatrix(m2);

  return 0;
}
