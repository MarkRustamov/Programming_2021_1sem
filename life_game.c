#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct point {
    unsigned is_alive:1;
};

const int height = 40;
const int width = 40;

int alive_number(struct point world[][height])
{
    unsigned int count = 0;
    unsigned i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (world[i][j].is_alive == 1) {
                count++;
            }
        }
    }
    return count;
}

void neighbours(int neighb[][2], int x, int y)
{
    int k = 0;
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) {
                continue;
            }
            neighb[k][0] = i;
            neighb[k][1] = j;
            k++;
        }
    }
}

int number_neighbors(struct point world[][height], int x, int y)
{
    int count = 0;
    int neighb[8][2];
    int _x_, _y_;

    neighbours(neighb, x, y);

    for (int i = 0; i < 8; i++) {
        _x_ = neighb[i][0];
        _y_ = neighb[i][1];

        if (_x_ < 0 || _y_ < 0) {
            continue;
        }
        if (_x_ >= width || _y_ >= height) {
            continue;
        }

        if (world[_x_][_y_].is_alive == 1) {
            count++;
        }
    }

    return count;
}

void next(struct point world[][height], struct point prev_world[][height])
{
    int neighbours_alive;
    struct point p;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            p = prev_world[i][j];
            neighbours_alive = number_neighbors(prev_world, i, j);

            if (p.is_alive == 0) {
                if (neighbours_alive == 3) {
                    world[i][j].is_alive = 1;
                }
            } else {
                if (neighbours_alive < 2 || neighbours_alive > 3) {
                    world[i][j].is_alive = 0;
                }
            }
        }
    }
}

void cpyworld(struct point first[][height], struct point result[][height])
{
    unsigned int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            result[i][j] = first[i][j];
        }
    }
}

int cmpworld(struct point world1[][height], struct point world2[][height])
{
    unsigned int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (world1[i][j].is_alive != world2[i][j].is_alive) {
                return -1;
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    struct point world[width][height];
    struct point prev_world[width][height];

    FILE *fin, *fout;
    fin = fopen(argv[2], "r");
    
    char bmpheader[62];
    for (int i = 0; i < 62; i++){
        bmpheader[i] = fgetc(fin);
    }
    int symbol;
    int bit;
    int shift = 7;
    for (int i = width - 1; i > -1; i--){
        for (int j = 0; j < height / 8; j++){
            symbol = fgetc(fin);
            while (symbol > 0){
                bit = symbol % 2;
                symbol = symbol / 2;
                if (bit == 1){
                    world[i][j * 8 + shift].is_alive = 0;
                }
                else{
                    world[i][j * 8 + shift].is_alive = 1;
                }
                shift--;
            }
            if (shift > -1){
                while (shift > -1){
                    world[i][j * 8 + shift].is_alive = 1;
                    shift--;
                }
            }
            shift = 7;
        }
        fseek(fin, 3, SEEK_CUR);
    }
    fclose(fin);

    int alive_points = -1;
    int optimal = 0;
    
    char zero = 0;
    int configuration = 1;
    char outputf[100];

    while (alive_points != 0 && optimal == 0){

        sprintf(outputf, "%s\\%d.bmp", argv[4], configuration);

        fout = fopen(outputf, "w");
        fwrite(bmpheader, 1, 62, fout);
        
        for (int i = width - 1; i > -1; i--){
            for (int j = 0; j < height / 8; j++){
                shift = 7;
                int power = 1;
                int result = 0;
                while (shift > -1){
                    if (world[i][j * 8 + shift].is_alive == 0){
                        result = result + power;
                    }
                    shift--;
                    power = power * 2;
                }
                unsigned char res = result;
                fprintf(fout, "%c", res);
            }
            fprintf(fout, "%c", zero);
            fprintf(fout, "%c", zero);
            fprintf(fout, "%c", zero);
        }
        fclose(fout);
        configuration++;
        
        cpyworld(world, prev_world);
        next(world, prev_world);

        optimal = cmpworld(world, prev_world) == 0;
        alive_points = alive_number(world);
    } 

    return 0;
}