#pragma once
#include "maths.h"


typedef struct particle{
    pe_vec2 position;
    pe_vec2 velocity;
    pe_vec2 acceleration;
    pe_vec2 size;

    float damping;
    float inv_mass;
}particle;


void integrate(float duration, particle * a);