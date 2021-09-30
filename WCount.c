#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
  FILE *fin;
  fin = fopen(argv[2], "r");
  int capitalword_number = 0, bytes_number = 0, lines_number = 1, words_number = 1; 
  char symbol, previous_symbol;

  while ((symbol = getc(fin)) != EOF)  {
    if (symbol == ' '){
      if (previous_symbol !=' '){
        words_number++;
      }
    } 
    if (symbol == '\n'){
      lines_number++;
      words_number++;
      bytes_number++;
    }
    if (( (previous_symbol == ' ') || (previous_symbol == '\n')) && (symbol >= 'A') && (symbol <= 'Z')){
      capitalword_number++;
    }
    bytes_number++;
    previous_symbol = symbol;
  }
  
  if ((strcmp(argv[1],"-l")==0) || (strcmp(argv[1],"--lines")==0)){
    printf("%d\n", lines_number);
  }
  if ((strcmp(argv[1],"-c")==0) || (strcmp(argv[1],"--bytes")==0)){
    printf("%d\n", bytes_number);
  }
  if ((strcmp(argv[1],"-w")==0) || (strcmp(argv[1],"--words")==0)){
    printf("%d\n", words_number);
  }
  if ((strcmp(argv[1],"-s")==0) || (strcmp(argv[1],"--cwords")==0)){
    printf("%d\n", capitalword_number);
  }
  fclose(fin);
  return 0;
}