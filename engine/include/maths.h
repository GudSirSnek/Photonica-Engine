

#define pi 3.14159265358979

#define pe_deg_to_rad(deg) deg*(pi/180)
#define pe_rad_to_deg(rad) rad *(180/pi)
#define pe_square(e) e*e
#define pe_1dDist(c1, c2) c2 - c1

int pe_dist2D(int x1, int y1, int x2, int y2);

typedef struct{
    int x, y;
}pe_vec2;