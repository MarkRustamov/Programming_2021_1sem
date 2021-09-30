#include <stdio.h>
  
int main()
{
  long int number_a, chislo, key, i;
  FILE *fin, *fout;
  fin = fopen("sort1_1.txt", "r");
  fout = fopen("sort1_2.txt", "w");
  fscanf(fin, "%d\n", number_a);
  long int a[number_a];
  for(i=0; i < number_a; i++){
      a[i] = fscanf(fin, "%d", chislo);
  }
  for (int j = 1; i < number_a; i++){
    key = a[j];
    i = j-1;
    while ((i > 0) && (a[i] > key))
    {
      a[i+1] = a[i];
      i--;
    }
    a[i+1] = key;
  }
  for(i=0; i < number_a; i++){
      fprintf(fout, "%d", a[i]);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}