#include <stdio.h>
#include <math.h>

#define LINESIZE 256
#define NUM 100

double sum(double numbers[]);
double sort_sum(double numbers[]);

int main(int argc, char *argv[])
{
  FILE *fp;
  char str[LINESIZE];
  double numbers[NUM], s, s_sorted;
  int i;

  if (argc < 2) {
    printf("Usage: ./No1_A [filename]\n");
    return 0;
  }
  
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Failed to open the file...\n");
    return -1;
  }

  i = 0;
  while (fscanf(fp, "%lf", &numbers[i]) != EOF && i < NUM) {
    i++;
  }
  
  s = sum(numbers);

  printf("sum: %lf\n", s);

  s = sort_sum(numbers);

  printf("sum(sorted): %lf\n", s);

  fclose(fp);
  return 0;
}


double sum(double numbers[])
{
  double s;
  int i;

  s = 0;
  for (i=0; i<NUM; i++) {
    s += numbers[i];
  }

  return s;
}

double sort_sum(double numbers[])
{
  double s, tmp;
  int i, j;

  /* bubble sort */
  for (i=0; i<(NUM-1); i++) {
    for (j=(NUM-1); j>i; j--) {
      if (fabs(numbers[j-1]) > fabs(numbers[j])) {
	tmp = numbers[j-1];
	numbers[j-1] = numbers[j];
	numbers[j] = tmp;
      }
    }
  }

  s = sum(numbers);
  
  return s;
}
