#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Prompt the user for the file to open and read the contents
 * into an array of floats.
 *
 * @param array The array to write into.
 * @param length The number of lines to read.
 * @return 1 if successful, 0 otherwise.
 */
int read_input_file(float * array, int length) {
  char buffer[64]; // Buffer for processing input

  // Prompt user for filename
  printf("File to open: ");
  fgets(buffer, sizeof(buffer), stdin);
  
  // Strip newline character 
  int len = strlen(buffer);
  if(buffer[len-1] == '\n') {
    buffer[len-1] = '\0';
  }

  // Try to open the file
  FILE * file = fopen(buffer, "r");
  if (file == NULL) {
    printf("Error: File \"%s\" does not exist!\n", buffer);
    return 0;
  }

  // Read file contents into array
  // If the file is too short, the last line will 
  // simply be repeated by fgets
  for(int i = 0; i < length; i++) {
    fgets(buffer, sizeof(buffer), file);
    
    char * endptr;
    array[i] = strtof(buffer, &endptr);

    if (*endptr != '\n') {
      printf("Error: Invalid input \"%s\" on line %d\n", buffer, i + 1);
      fclose(file);
      return 0;
    }
  }

  fclose(file);
  return 1;
}

// Store month names for quick reference
static const char * months[12] = {
  "January", "February", "March",
  "April", "May", "June",
  "July", "August", "September",
  "October", "November", "December"
};

/**
 * Get the average of a float array between two indices (inclusive)
 *
 * @param array The array to average
 * @param start The first index
 * @param end The last index
 * @return The average between the indices
 */
float slice_average(float *data, int start, int end) {
  float sum = 0;

  for(int i = start; i <= end; i++) {
    sum += data[i];
  }

  return sum / (end - start + 1);
}

/**
 * Print the given monthly sales data in a readable format
 * 
 * @param data An array of 12 floats corresponding to monthly sales figures
 * @param year The year to label the data with
 */ 
void print_monthly_sales_report(float * data, int year) {
  printf("Monthly Sales Report for %d\n\n", year);
  printf("Month     Sales\n");

  for(int i = 0; i < 12; i++) {
    printf("%-9s %.2f\n", months[i], data[i]);
  }
  printf("\n\n");
}

/**
 * Print a summary including minimum, maximum, and average sales
 *
 * @param data An array of 12 floats corresponding to monthly sales figures
 */
void print_sales_summary(float *data) {
  int min_i = 0, max_i = 0;
  float sum = 0;

  for(int i = 0; i < 12; i++) {
    if (data[i] < data[min_i])
      min_i = i;
    if (data[i] > data[max_i])
      max_i = i;

    sum += data[i];
  }

  printf("Sales summary report:\n\n");
  printf("Minimum sales: %.2f (%s)\n", data[min_i], months[min_i]);
  printf("Maximum sales: %.2f (%s)\n", data[max_i], months[max_i]);
  printf("Average sales: %.2f\n\n\n", sum / 12.0);
}

/**
 * Print the six-month moving average report
 *
 * @param data An array of 12 floats corresponding to monthly sales figures
 */
void print_six_month_moving_average(float *data) {
  printf("Six-Month moving average report:\n\n");

  for(int i = 0, j = 5; i < 7; i++, j++) {
    printf(
      "%s-%s\t%.2f\n",
      months[i],
      months[j],
      slice_average(data, i, j)
    );
  }
  printf("\n\n");
}

/**
 * Swaps the values of two int pointers
 */
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * For recursive calls from `quicksort_indices`
 */ 
void quicksort_indices_rec(float *arr, int *ind, int low, int high) {
  if (low >= high || low < 0)
    return;

  int i = low;

  // Partition the array
  for(int j = low; j < high; j++) {
    if (arr[ind[j]] <= arr[ind[high]]) {
      swap(&ind[i], &ind[j]);
      i++;
    }
  }

  swap(ind+i, ind+high);

  quicksort_indices_rec(arr, ind, low, i - 1);
  quicksort_indices_rec(arr, ind, i + 1, high);
}

/**
 * Sort the indices of an array without altering the original array
 *
 * @param arr The array to sort 
 * @param ind An array of equal length to store indices in 
 * @param length The length of `arr`
 */
void quicksort_indices(float *arr, int *ind, int length) {
  for(int i = 0; i < length; i++)
    ind[i] = i;

  quicksort_indices_rec(arr, ind, 0, length - 1);
}

/**
 * Print a monthly sales report in descending order by sales figure
 *
 * @param data An array of 12 floats corresponding to monthly sales figures. 
 */
void print_sorted_sales_report(float *data) {
  int indices[12]; // for preserving the order of the months along with the sales data
  quicksort_indices(data, indices, 12);

  printf("Sales report (highest to lowest):\n\n");
  printf("Month     Sales\n");

  // Print in descending order
  for (int i = 11; i >= 0; i--) {
    printf("%-9s %.2f\n", months[indices[i]], data[indices[i]]);
  } 
  printf("\n\n");
}

int main() {
  // Get sales data
  float figures[12];
  int success = read_input_file(figures, 12);
  if (!success)
    return 1;

  // Print the report
  print_monthly_sales_report(figures, 2024);
  print_sales_summary(figures);
  print_six_month_moving_average(figures);
  print_sorted_sales_report(figures);

  return 0;
}
