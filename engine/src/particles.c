#include "particles.h"

pe_vec2 gravity = {0.0, 1.0};

void integrate(float duration, particle * a){

    a->position[0] += a->velocity[0]*duration + a->acceleration[0]*duration*duration*0.5;
    a->position[1] += a->velocity[1]*duration + a->acceleration[1]*duration*duration*0.5;

    pe_vec2 working_acc = {a->acceleration[0],a->acceleration[1]};

    working_acc[0] += gravity[0];
    working_acc[1] += gravity[1];


    a->velocity[0] += working_acc[0]*duration;
    a->velocity[1] += working_acc[1]*duration;

    a->velocity[0] *=  pow(a->damping, duration);
    a->velocity[1] *=  pow(a->damping, duration);


}