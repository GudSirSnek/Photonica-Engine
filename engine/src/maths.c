#include "maths.h"

int pe_dist2D(int x1, int y1, int x2, int y2){
    int square_difference_x = (x2-x1)*(x2-x1);
    int square_difference_y = (y2-y1)*(y2-y1);
    int sum = square_difference_x + square_difference_y;
    int value = sqrt(sum);
    return value;
}

void vec4_scale(pe_vec4 r, pe_vec4 const v, float const s){
    for(int i = 0; i < 4; i++){
        r[i] = v[i]*s;
    }
}

void vec4_dup(pe_vec4 r, pe_vec4 const src){
    for (int i = 0; i<4; i++){
        r[i] = src[i];
    }
}

void M4x4_identity(M4x4 mat){
    
    memset(mat, 0, 64);

    for (int i = 0; i<4; i++){
        mat[i][i] = 1;
    }
}

void M4x4_translate(M4x4 T, float x, float y, float z){
	T[3][0] = x;
	T[3][1] = y;
	T[3][2] = z;
}

void M4x4_scale_aniso(M4x4 M, M4x4 const a, float x, float y, float z){
    vec4_scale(M[0], a[0], x);
	vec4_scale(M[1], a[1], y);
	vec4_scale(M[2], a[2], z);
	vec4_dup(M[3], a[3]);

}


void M4x4_ortho(M4x4 M, float l, float r, float b, float t, float n, float f){
    M[0][0] = 2.f/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f/(f-n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;
	
	M[3][0] = -(r+l)/(r-l);
	M[3][1] = -(t+b)/(t-b);
	M[3][2] = -(f+n)/(f-n);
	M[3][3] = 1.f;
}