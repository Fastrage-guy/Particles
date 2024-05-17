#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include "particle.h"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

using namespace std;

float targetFPS = 60;
float targetFrameTime = 1000/targetFPS;
chrono::system_clock::time_point a = chrono::system_clock::now();
chrono::system_clock::time_point b = chrono::system_clock::now();

int main(int argc, char** argv){
    srand (time(NULL));
    if(SDL_Init(SDL_INIT_VIDEO) < 0) { printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError()); return 1; }
    SDL_Window *window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){ printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError()); return 1; }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) { printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError()); return 1; }

    std::vector<Particle> particles;

    for (int i = 0; i < 512; i++) {
        particles.push_back(Particle(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
    }

    bool running = true;
    while(running) {
        // FPS capping and monitoring
        a = chrono::system_clock::now();
        chrono::duration<double, milli> work_time = a - b;

        if (work_time.count() < targetFrameTime) {
            chrono::duration<double, milli> delta_ms(targetFrameTime - work_time.count());
            auto delta_ms_duration = chrono::duration_cast<chrono::milliseconds>(delta_ms);
            this_thread::sleep_for(chrono::milliseconds(delta_ms_duration.count()));
        }

        b = chrono::system_clock::now();
        chrono::duration<double, milli> sleep_time = b - a;
        float deltaTime = (work_time + sleep_time).count();

        cout << 1000 / deltaTime << endl;

        // Event handling
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
            }
        }

        // Updating
        for (Particle &i : particles) {
            float ax = 0;
            float ay = 0;
            for (Particle &j : particles) {
                if (&i == &j) continue;
                float dx = j.x - i.x;
                float dy = j.y - i.y;
                float distance = sqrt(dx * dx + dy * dy) + 10;
                float force = 1 / (distance * distance);
                float nx = dx / distance;
                float ny = dy / distance;
                ax += nx * force;
                ay += ny * force;
            }
            i.accelerate(ax, ay, 1);
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (Particle &i : particles) {
            i.update(1);
            SDL_SetRenderDrawColor(renderer, i.r, i.g, i.b, 255);
            SDL_Rect r = {(int)i.x, (int)i.y, 2, 2};
            SDL_RenderFillRect(renderer, &r);
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}