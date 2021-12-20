#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int maximum = 1000000000;

typedef struct {
    int *numbers;
    int length;
} uint1024_t;

uint1024_t init() {
    uint1024_t num;
    num.length = 0;
    num.numbers = NULL;
    return num;
}

uint1024_t len_init(int len) {
    uint1024_t num;
    num.length = len;
    num.numbers = calloc(len, sizeof(int));
    return num;
}

uint1024_t from_uint(unsigned int x) {
    int len;
    if (x >= maximum){
        len = 2;
    }
    else{
        len = 1;
    }
    uint1024_t num = len_init(len);
    num.numbers[0] = (int) (x % maximum);
    if (len > 1){
        num.numbers[1] = (int) (x / maximum);
    }
    return num;
}

void zero_del(uint1024_t *x) {
    int size = x->length;
    while (x->length-1 > 0 && x->numbers[x->length-1] == 0){
        x->length--;
    }
    if (size == x->length){
        return;
    }
}

void scanf_value(uint1024_t *x) {
    char num_char[310];
    scanf("%309s", num_char);
    int help = 0, size = strlen(num_char);
    int num_count;
    if (size % 9 == 0){
        num_count = size/9;
    }
    else{
        num_count = (size/9)+1;
    }
    *x = len_init(num_count);
    int num_len = 0;
    for (int i = size-9; i >= 0; i-=9) {
        int j = i;
        while (j-i < 9) {
            help = help*10 + num_char[j]-'0';
            j++;
        }
        x->numbers[num_len++] = help;
        help = 0;
    }
    for (int i = 0; i < size-num_len*9; ++i){
        help = help*10 + num_char[i]-'0';
    }
    if (num_len < num_count){
        x->numbers[num_count-1] = help;
    }
}

void printf_value(uint1024_t x) {
    printf("%u", x.numbers[x.length-1]);
    for (int i = x.length - 2; i >= 0; --i){
        printf("%09u", x.numbers[i]);
    }
    printf("\n\n");
}

uint1024_t add_op(uint1024_t x, uint1024_t y) {
    if (x.length < y.length) {
        uint1024_t help = x;
        x = y;
        y = help;
    }
    int transposition = 0;
    uint1024_t result = len_init(x.length);
    for (int i = 0; i < x.length; ++i) {
        result.numbers[i] = transposition + x.numbers[i] + (i < y.length ? y.numbers[i] : 0);
        transposition = 0;
        if (result.numbers[i] >= maximum) {
            transposition++;
            result.numbers[i] -= maximum;
        }
    }
    if (transposition > 0){
        result.length++;
        result.numbers[result.length - 1] = transposition;
    }
    return result;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y) {
    int max;
    if (x.length > y.length){
        max = x.length;
    }
    else{
        max = y.length;
    }
    uint1024_t result = len_init(max);
    int transposition = 0;
    for (int i = 0; i < max; ++i) {
        result.numbers[i] = (i < x.length ? x.numbers[i] : 0) - transposition - (i < y.length ? y.numbers[i] : 0);
        transposition = 0;
        if (result.numbers[i] < 0) {
            transposition++;
            result.numbers[i] += maximum;
        }
    }
    zero_del(&result);
    return result;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y) {
    int length = x.length + y.length;
    uint1024_t result = len_init(length);
    for (int i = 0; i < x.length; i++) {
        int transposition = 0, last = 0;
        for (int j = 0; j < y.length; j++) {
            long long multiplication = (long long) x.numbers[i] * (long long) (j < y.length ? y.numbers[j] : 0);
            long long help = result.numbers[i + j] + multiplication + transposition;
            result.numbers[i + j] = (int) (help % maximum);
            transposition = (int) (help / maximum);
            last = j+1;
        }
        if (transposition > 0)
            result.numbers[i + last] += transposition;
    }
    zero_del(&result);
    return result;
}

int main() {
    uint1024_t x = init();
    uint1024_t y = init();
    printf("First number: ");
    scanf_value(&x);
    printf("Second number: ");
    scanf_value(&y);
    uint1024_t add = add_op(x, y);
    uint1024_t sub = subtr_op(x, y);
    uint1024_t mult = mult_op(x, y);
    printf("addition\n");
    printf_value(add);
    printf("subtraction\n");
    printf_value(sub);
    printf("multiplication\n");
    printf_value(mult);
    return 0;
}