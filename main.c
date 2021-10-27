#include <stdio.h>

const unsigned long int max_ulint = 4294967295;

typedef struct uint1024_t{
    unsigned long int array[32];
}uint1024_t;

uint1024_t from_uint(unsigned int x){
    uint1024_t result;
    for (int i = 0; i < 32; i++){
        result.array[i] = 0;
    }
    result.array[31] = x;
    return result;
}

uint1024_t add_op(uint1024_t x, uint1024_t y){
    uint1024_t  result;
    for (int i = 0; i < 32; i++){
        result.array[i] = 0;
    }
    unsigned long long int sum = 0;
    for (int i = 31; i > 0; i--){
        sum = (unsigned long long int)x.array[i] + y.array[i] + result.array[i];
        if (sum <= max_ulint){
            result.array[i] = (unsigned long int) sum;
        }
        else{
            result.array[i] = (unsigned long int) sum - (sum / (max_ulint + 1)) * (max_ulint + 1);
            result.array[i-1] = (unsigned long int)sum / (max_ulint + 1);
        }
    }
    result.array[0] = x.array[0] + y.array[0] + result.array[0];
    return result;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y){
    uint1024_t  result;
    for (int i = 0; i < 32; i++){
        result.array[i] = 0;
    }
    long long int difference = 0;
    for (int i = 31; i > 0; i--){
        difference = (long long int) x.array[i] - y.array[i];
        if (difference < 0){
            if (x.array[i - 1] == 0){
                int j = i - 1;
                while (x.array[j] == 0){
                    j--;
                }
                x.array[j]--;
                j++;
                while (j != i){
                    x.array[j] = max_ulint;
                    j++;
                }
                result.array[i] = (unsigned long int) difference + max_ulint;
                result.array[i]++;
            }
            else {
                x.array[i - 1]--;
                result.array[i] = (unsigned long int) difference + max_ulint;
                result.array[i]++;
            }
        }
        result.array[i] = (unsigned long int) difference;
    }
    result.array[0] = x.array[0] - y.array[0];
    return result;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y){
    uint1024_t  result, stage_result;
    int temp = 0;
    for (int i = 0; i < 32; i++){
        result.array[i] = 0;
    }
    for (int i = 0; i < 32; i++){
        stage_result.array[i] = 0;
    }
    unsigned long long int product = 0;
    for (int i = 31; i > 0; i--){
        for (int j = 31; j > 0; j--){
            product = (unsigned long long int) x.array[i] * y.array[j];
            if (product <= max_ulint){
                stage_result.array[i+temp] = (unsigned long int) product;
            }
            else{
                stage_result.array[i+temp] = (unsigned long int) product - (product / (max_ulint + 1)) * (max_ulint + 1);
                stage_result.array[i+temp-1] = (unsigned long int)product / (max_ulint + 1);
            }
            temp++;
        }
        result = add_op(result, stage_result);
        for (int k = 0; k < 32; k++){
            stage_result.array[k] = 0;
        }
        temp = 0;
    }
    return result;
}

void scanf_value(struct uint1024_t* x){

}

int main() {

    return 0;
}
