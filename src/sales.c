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

// With fixed-width names for column printing
static const char * months_fixed[12] = {
  "January  ", "February ", "March    ",
  "April    ", "May      ", "June     ",
  "July     ", "August   ", "September",
  "October  ", "November ", "December "
};

/**
 * Print the average of a float array between two indices (inclusive)
 *
 * @param array The array to average
 * @param start The first index
 * @param end The last index
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
    printf("%s %.2f\n", months_fixed[i], data[i]);
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

int main() {
  // Get sales data
  float figures[12];
  int success = read_input_file(figures, 12);
  if (!success)
    return 1;

  print_monthly_sales_report(figures, 2024);
  print_sales_summary(figures);
  print_six_month_moving_average(figures);

  return 0;
}
