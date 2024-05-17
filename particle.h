#pragma once
#include <vector>

class Particle {
    public:
        float x = 0;
        float y = 0;
        float z = 0;
        float vx = 0;
        float vy = 0;
        float vz = 0;
        float r = 0;
        float g = 0;
        float b = 0;

        Particle();
        Particle(float x, float y);
        Particle(float x, float y, float z);

        void update(float dt, bool is3D=false);
        void accelerate(float ax, float ay, float dt);
        void accelerate(float ax, float ay, float az, float dt);
};