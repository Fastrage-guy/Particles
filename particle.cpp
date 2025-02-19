#include "particle.h"
#include <iostream>

using namespace std;

Particle::Particle() {
    x = 0;
    y = 0;
    z = 0;
    vx = 0;
    vy = 0;
    vz = 0;
    r = 255;
    g = 255;
    b = 255;
}

Particle::Particle(float x, float y) {
    this->x = x;
    this->y = y;
    this->z = 0;
    this->vx = 0;
    this->vy = 0;
    this->vz = 0;
    this->r = 255;
    this->g = 255;
    this->b = 255;
}

Particle::Particle(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->vx = 0;
    this->vy = 0;
    this->vz = 0;
    this->r = 255;
    this->g = 255;
    this->b = 255;
}

void Particle::update(float dt, bool is3D) {
    x += vx * dt;
    y += vy * dt;
    if(is3D) {
        z += vz * dt;
    }
}

void Particle::accelerate(float ax, float ay, float dt) {
    vx += ax * dt;
    vy += ay * dt;
}

void Particle::accelerate(float ax, float ay, float az, float dt) {
    vx += ax * dt;
    vy += ay * dt;
    vz += az * dt;
}