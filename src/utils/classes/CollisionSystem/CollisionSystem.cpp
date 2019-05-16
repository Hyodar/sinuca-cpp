
#include <SDL.h>

#include <iostream>
#include <vector>

#include "../Ball/Ball.h"

#include "CollisionSystem.h"

extern std::vector<Ball> gBalls;

// -----------------------------------------------------------------------------

void CollisionSystem::process() {
    this->checkAllCollisions();
}

// -----------------------------------------------------------------------------

void CollisionSystem::checkAllCollisions() {
    for(unsigned int i=0; i<gBalls.size(); i++) {
        for(unsigned int j=i+1; j<gBalls.size(); j++) {
            std::cout << "[] Checking collision between balls " << i << " and " << j << "...\n";
            gBalls[i].checkCollision(gBalls[j]);
        }

        std::cout << "[] Checking wall collision of ball " << i << "...\n";
        gBalls[i].wallCollision();
    }
}

// -----------------------------------------------------------------------------
