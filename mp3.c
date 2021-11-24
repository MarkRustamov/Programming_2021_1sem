#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
FILE *fin;
fin = fopen(argv[1], "r");
unsigned char frame[6], symbol, metainf[100];


if (strcmp(argv[2], "--show") == 0){
    fseek(fin, 10, SEEK_SET);
    for (int i = 0; i < 4; i++){
        frame[i] = getc(fin);
    }
    frame[4] = '\0';
    int counter = 0;
    fseek(fin, 7, SEEK_CUR);

    while (frame[0] >= 'A' && frame[0] <= 'Z'){
        symbol = getc(fin);
        while (symbol != '\0'){
           metainf[counter] = symbol;
           counter++;
           symbol = getc(fin);
        }
        printf(" %s:       ", frame);
        frame[0] = metainf[counter - 4];
        frame[1] = metainf[counter - 3];
        frame[2] = metainf[counter - 2];
        frame[3] = metainf[counter - 1];
        frame[4] = '\0';
        if (frame[0] >= 'A' && frame[0] <= 'Z'){
            fseek(fin, 6, SEEK_CUR);
            symbol = getc(fin);
            if (symbol != '\0'){
                metainf[counter - 4] = '\0';
                printf("%s\n", metainf);
                counter = 0;
                fseek(fin, -1, SEEK_CUR);
            }
            else{
                frame[0] = '0';
            }

        }
        else{
            metainf[counter] = '\0';
            printf("%s\n", metainf);
        }
    }
}
	
if (strncmp(argv[2], "--get=", 5) == 0){
    frame[0] = '=';
    char* end_of_line = strrchr(argv[2], '=');
    int f = 1;
    fseek(fin, 10, SEEK_SET);
    
    for (int i = 1; i < 6; i++){
        frame[i] = getc(fin);
    }

    while (f == 1){
        fseek(fin, 6, SEEK_CUR);
        if (strcmp(end_of_line, frame) == 0){
            int counter = 0;
            symbol = getc(fin);
            while (symbol != '\0'){
                metainf[counter] = symbol;
                counter++;
                symbol = getc(fin);
            }
            if (counter <= 4){
                metainf[counter] = '\0';
                frame[0] = ' ';
                printf("%s:       %s", frame, metainf);
                f = 0;
            }
            else{
                metainf[counter - 4] = '\0';
                frame[0] = ' ';
                printf("%s:       %s", frame, metainf);
                f = 0;
            }
        }
        else{
            fseek(fin, 6, SEEK_CUR);
            while (symbol != '\0'){
                symbol = getc(fin);
            }
            fseek(fin, 6, SEEK_CUR);
            symbol = getc(fin);
            if (symbol != '\0'){
                fseek(fin, -12, SEEK_CUR);
                for (int i = 1; i < 6; i++){
                    frame[i] = getc(fin);
                }
            }
            else{

                printf("None\n");
                f = 0;
            }
        }
    }
}

if (strncmp(argv[2], "--set=", 5) == 0){
    FILE *fout;
    fout = fopen("C:/Users/irmar/Desktop/Prog/New.mp3", "w");
    fseek(fin, 0L, SEEK_END);
    long long int size = ftell(fin);
    rewind(fin);
    unsigned char* value_n = strrchr(argv[3], '=');
    unsigned char* frame_n = strrchr(argv[2], '=');

    unsigned char value_name[40];
    unsigned char frame_name[10];
    //frame_name[0] = '=';
    int i = 1;
    while (i < strlen(frame_n)){
        frame_name[i-1] = frame_n[i];
        i++;
    }
    frame_name[i-1] = '\0';

    i = 1;
    while (i < strlen(value_n)){
        value_name[i-1] = value_n[i];
        i++;
    }
    value_name[i-1] = '\0';
    value_n = value_name;
    symbol = ' ';

    for (i = 0; i < 4; i++){
        symbol = fgetc(fin);
        fputc(symbol, fout);
        frame[i] = symbol;
    }
    frame[4] = '\0';
    long long int current = 0;

    while (current < size){
        symbol = fgetc(fin);
        frame[0] = frame[1];
        frame[1] = frame[2];
        frame[2] = frame[3];
        frame[3] = symbol;
        fputc(symbol, fout);
        if (strcmp(frame, frame_name) == 0){
            for (i = 0; i < 7; i++){
                symbol = fgetc(fin);
                fputc(symbol, fout);
            }
            fputs(value_n, fout);
            symbol = '0';
            while (symbol != '\0'){
                symbol = fgetc(fin);
            }
            fseek(fin, -5, SEEK_CUR);
        }
        current++;
    }
    fclose(fout);
}

fclose(fin);

return 0;
}