#include <maths.h>
#include <math.h>
int pe_dist2D(int x1, int y1, int x2, int y2){
    int square_difference_x = (x2-x1)*(x2-x1);
    int square_difference_y = (y2-y1)*(y2-y1);
    int sum = square_difference_x + square_difference_y;
    int value = sqrt(sum);
    return value;
}