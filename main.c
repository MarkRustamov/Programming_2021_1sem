#include <stdio.h>
#include <string.h>

typedef struct uint1024_t{
    unsigned int array[309];
}uint1024_t;

uint1024_t from_uint(unsigned int x){
    uint1024_t result;
    int i = 0;
    while (x > 0){
        result.array[i] = x % 10;
        x = x / 10;
        i++;
    }
    for (int j = i; j < 309; j++){
        result.array[j] = 0;
    }
    return result;
}

uint1024_t add_op(uint1024_t x, uint1024_t y){
    uint1024_t  result;
    for (int i = 0; i < 309; i++){
        result.array[i] = 0;
    }
    unsigned int sum;
    for (int i = 308; i > 0; i--){
        sum = x.array[i] + y.array[i] + result.array[i];
        if (sum <= 9){
            result.array[i] = sum;
        }
        else{
            result.array[i] = sum % 10;
            result.array[i-1] = sum / 10;
        }
    }
    result.array[0] = x.array[0] + y.array[0] + result.array[0];
    return result;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y){
    uint1024_t  result;
    for (int i = 0; i < 309; i++){
        result.array[i] = 0;
    }
    unsigned int difference;
    for (int i = 308; i > 0; i--){
        difference = x.array[i] - y.array[i];
        if (difference < 0){
            if (x.array[i - 1] == 0){
                int j = i - 1;
                while (x.array[j] == 0){
                    j--;
                }
                x.array[j]--;
                j++;
                while (j != i){
                    x.array[j] = 9;
                    j++;
                }
                result.array[i] = difference + 10;
                result.array[i]++;
            }
            else {
                x.array[i - 1]--;
                result.array[i] = difference + 10;
                result.array[i]++;
            }
        }
        result.array[i] = difference;
    }
    result.array[0] = x.array[0] - y.array[0];
    return result;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y){
    uint1024_t  result, stage_result;
    int temp = 0;
    for (int i = 0; i < 309; i++){
        result.array[i] = 0;
    }
    for (int i = 0; i < 32; i++){
        stage_result.array[i] = 0;
    }
    unsigned int product;
    for (int i = 309; i > 0; i--){
        for (int j = 309; j > 0; j--){
            product = x.array[i] * y.array[j];
            stage_result.array[i+temp] = product + stage_result.array[i+temp];
            if (stage_result.array[i+temp] > 9){
                stage_result.array[i+temp-1] = stage_result.array[i+temp] / 10;
                stage_result.array[i+temp] = stage_result.array[i+temp] % 10;
            }
            temp++;
        }
        result = add_op(result, stage_result);
        for (int k = 0; k < 309; k++){
            stage_result.array[k] = 0;
        }
        temp = 0;
    }
    return result;
}

void printf_value(uint1024_t x){
    int j = 308;
    while (x.array[j] == 0){
        j--;
    }
    if (j == -1){
        printf("0");
    }
    else {
        for (int i = 0; i <= j; i++) {
            printf("%u", x.array[i]);
        }
    }
    printf("\n");
    printf("\n");
}

void scanf_value(uint1024_t* x){
    char number[309];
    for (int i = 0; i < 309; i++){
        number[i] = '0';
    }
    scanf("%s", number);
    for (int i = 0; i < 309; i++){
        x->array[i] = 0;
    }
    for (int i = 0; i < strlen(number); i++){
        x->array[i] = number[i] - '0';
    }
    for (int i = strlen(number); i < 309; i++){
        x->array[i] = 0;
    }
}

int main() {
    uint1024_t first_number, second_number, sum_result, difference_result, product_result;
    scanf_value(&first_number);
    scanf_value(&second_number);
    sum_result = add_op(first_number, second_number);
    difference_result = subtr_op(first_number, second_number);
    product_result = mult_op(first_number, second_number);
    printf_value(sum_result);
    printf_value(difference_result);
    printf_value(product_result);
    printf_value(first_number);
    printf_value(second_number);
    return 0;
}