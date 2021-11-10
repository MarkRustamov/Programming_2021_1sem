#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin, *fout;
    fin = fopen("access_log_Jul95.txt", "r");
    fout = fopen("Answers.txt", "w");
    char string[400], max_requesttime[27], const_time[6];
    char *check;
    int error_counter = 0, max_requests = -1, time_requests = 0;
    while (1){
        check = fgets (string, sizeof(string), fin);
        if (check == NULL){
            break;
        }
        unsigned int i = strlen(string) - 1;
        while (string[i] != '"'){
            i--;
        }
        if (string[i+2] == '5'){
            error_counter++;
            unsigned int right_quotes = i;
            while (string[i-1] != '"'){
                i--;
            }
            fprintf(fout, "%d) ", error_counter);
            for (unsigned int left_quotes = i; left_quotes < right_quotes; left_quotes++){
                fprintf(fout, "%c", string[left_quotes]);
            }
            fprintf(fout, "\n");
        }
        i = 0;
        char time[6];
        while (string[i] != ']'){
            i++;
        }
        time[0] = string[i-11];
        time[1] = string[i-10];
        time[2] = string[i-9];
        time[3] = string[i-8];
        time[4] = string[i-7];
        time[5] = '\0';
        if (strncmp(time, const_time, 5) == 0){
            time_requests++;
        }
        else{
            strcpy(const_time, time);
            if (time_requests > max_requests){
                max_requests = time_requests;
                i--;
                int j = 25;
                max_requesttime[26] = '\0';
                while (string[i] != '['){
                    max_requesttime[j] = string[i];
                    j--;
                    i--;
                }
            }
            time_requests = 0;
        }
    }
    fprintf(fout, "<><><><><><><><><><><><><><><><>\n");
    fprintf(fout, "Number of errors is %d\n", error_counter);
    fprintf(fout, "<><><><><><><><><><><><><><><><>\n");
    fprintf(fout, "Max request time is %s\nMax number of requests is %d", max_requesttime, max_requests-1);
    fclose(fin);
    fclose(fout);
    return 0;
}
