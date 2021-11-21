#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin, *fout;
    fin = fopen("access_log_Jul95.txt", "r");
    fout = fopen("Answers.txt", "w");
    char string[300];
    char *check;
    int error_counter = 0, time_array[1900000], time_counter = 0, time_interval, interval_requests, max_requests = -1;
    scanf("%d", &time_interval);
    while (1){
        check = fgets (string, sizeof(string), fin);
        if (check == NULL){
            break;
        }
        unsigned long i = strlen(string) - 1;
        while (string[i] != '"'){
            i--;
        }
        if (string[i+2] == '5'){
            error_counter++;
            unsigned long right_quotes = i;
            while (string[i-1] != '"'){
                i--;
            }
            fprintf(fout, "%d) ", error_counter);
            for (unsigned long left_quotes = i; left_quotes < right_quotes; left_quotes++){
                fprintf(fout, "%c", string[left_quotes]);
            }
            fprintf(fout, "\n");
        }
        i = 0;
        while (string[i] != '['){
            i++;
        }
        time_array[time_counter] = ((string[i+1] - '0') * 10 + (string[i+2] - '0')-1) * 24 * 3600;
        time_array[time_counter] += ((string[i+13] - '0') * 10 + (string[i+14] - '0')) * 3600;
        time_array[time_counter] += ((string[i+16] - '0') * 10 + (string[i+17] - '0')) * 60;
        time_array[time_counter] += (string[i+19] - '0') * 10 + (string[i+20] - '0');
        time_counter++;
    }
    int i = 0;
    while(i < time_counter) {
        interval_requests = 1;
        if(time_array[i] != time_array[i - 1] || i == 0) {
            int j = i + 1;
            while (time_array[j] - time_array[i] < time_interval && j < time_counter){
                interval_requests++;
                j++;
            }
        }

        if(interval_requests > max_requests)
            max_requests = interval_requests;
        i++;
    }
    fprintf(fout, "<><><><><><><><><><><><><><><><>\n");
    fprintf(fout, "Number of errors is %d\n", error_counter);
    fprintf(fout, "<><><><><><><><><><><><><><><><>\n");
    fprintf(fout, "Max number of requests is %d", max_requests);
    fclose(fin);
    fclose(fout);
    return 0;
}
