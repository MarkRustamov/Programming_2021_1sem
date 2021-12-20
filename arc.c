#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (strcmp(argv[2], "--create") == 0){
        FILE *fdat;
        fdat = fopen(argv[1], "w");
        for (int i = 3; i < argc; i++){
            char zero = 0;
            for (int j = 0; j < 10; j++){
                fprintf(fdat, "%c", zero);
            }
            FILE *fin;
            fin = fopen(argv[i], "r");
            char* name_of_file = strrchr(argv[i], '\\');
            fprintf(fdat, "%s", name_of_file);
            fprintf(fdat, "%c", zero);
            fseek(fin, 0L, SEEK_END); 
            long long int size = ftell(fin); 
            rewind(fin); 
            long long int current = 0;
            fprintf(fdat, "%lld", size);
            fprintf(fdat, "%c", zero);
            while (current < size){
                char symbol = fgetc(fin);
                fputc(symbol, fdat);
                current++;
            }
            fclose(fin);
        }
        fclose(fdat);
    }

    if (strcmp(argv[2], "--list") == 0){
        FILE *fdat;
        fdat = fopen(argv[1], "r");
        int null_counter = 0;
        char symbol;
        fseek(fdat, 0L, SEEK_END); 
        long long int size = ftell(fdat);
        rewind(fdat);
        long long int current = 0;
        while (current < size){
            symbol = fgetc(fdat);
            current++;
            if (symbol == '\0'){
                null_counter++;
            }
            else if (null_counter == 10 && symbol == '\\'){
                char name[20];
                int i = 0;
                while (symbol != '\0'){
                    symbol = fgetc(fdat);
                    name[i] = symbol;
                    i++;
                    current++;
                }
                name[i] = symbol;
                printf("%s\n", name);
                null_counter = 0;
            }
            else if (null_counter > 0 && symbol != '\\'){
                null_counter = 0;
            }
        }
        fclose(fdat);
    }

    if (strcmp(argv[2], "--extract") == 0){
        FILE *fdat;
        fdat = fopen(argv[1], "r");
        char symbol;
        fseek(fdat, 0L, SEEK_END); 
        long long int size = ftell(fdat);
        rewind(fdat);
        long long int current = 0;
        while (current < size){
            for (int i = 0; i < 10; i++){
                symbol = fgetc(fdat);
                current++;
            }
            symbol = 'c';
            char name[20];
            int i = 0;
            while (symbol != '\0'){
                symbol = fgetc(fdat);
                name[i] = symbol;
                i++;
                current++;
            }
            name[i] = symbol;
            symbol = 'c';
            char file_size[10];
            i = 0;
            while (symbol != '\0'){
                symbol = fgetc(fdat);
                file_size[i] = symbol;
                i++;
                current++;
            }
            file_size[i] = symbol;
            long long int size_number = atoi(file_size);
            long long int cur = 0;
            char output[120];
            sprintf(output, "C:/Users/irmar/Desktop/Prog/extract%s", name);
            FILE *fout;
            fout = fopen(output, "w");
            while (cur < size_number){
                symbol = fgetc(fdat);
                fputc(symbol, fout);
                cur++;
                current++;
            }
            fclose(fout);
        }
        fclose(fdat);
    }
    return 0;
}