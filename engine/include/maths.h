

#define pi 3.14159265358979

#define pe_deg_to_rad(deg) deg*(pi/180)
#define pe_rad_to_deg(rad) rad *(180/pi)
#define pe_square(e) e*e
#define pe_1dDist(c1, c2) c2 - c1

int pe_dist2D(int x1, int y1, int x2, int y2);

typedef float pe_vec2[2];

typedef float pe_vec3[3];


typedef float pe_vec4[4];


typedef pe_vec4 M4x4[4];


void M4x4_identity(M4x4 mat);

void M4x4_translate(M4x4 mat, float x, float y, float z);

void M4x4_scale_aniso(M4x4 M, M4x4 const a, float x, float y, float z);

void vec4_scale(pe_vec4 r, pe_vec4 const v, float const s);
void vec4_dup(pe_vec4 r, pe_vec4 const src);