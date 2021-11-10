#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fin, *fout;
    fin = fopen("access_log_Jul95.txt", "r");
    fout = fopen("Answers.txt", "w");
    char string[400], max_requestdate[2], const_date[2];
    char *check;
    int error_counter = 0, max_requests = -1, date_requests = 0;
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
        char date[2];
        while (string[i] != '['){
            i++;
        }
        date[0] = string[i+1];
        date[1] = string[i+2];
        //fprintf(fout, "%c%c", date[0], date[1]);
        if ((strcmp(const_date, date)) == 0){
            date_requests++;
        }
        else{
            const_date[0] = date[0];
            const_date[1] = date[1];
            if (date_requests > max_requests){
                max_requests = date_requests;
                max_requestdate[0] = date[0];
                max_requestdate[1] = date[1];
            }
            date_requests = 0;
        }
        //fprintf(fout, "%c", lastspace_position+2);
    }
    /*unsigned int counter = 0;
    while ((check = fgets (string, sizeof(string), fin)) != NULL){
        fprintf(fout, '%s', string);

    }*/
    fprintf(fout, "\n");
    fprintf(fout, "Number of errors is %d\n", error_counter);
    fprintf(fout, "%c%c/Jul/1995  %d", max_requestdate[0], max_requestdate[1], max_requests);
    fclose(fin);
    fclose(fout);
    return 0;
}
