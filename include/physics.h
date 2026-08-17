#ifndef PHYSICS_H
#define PHYSICS_H
#include "simulation.h"

void resetBodyAcceleration(Body *body);

void applyGravityForBodyPair(SimulationState *state, Body *bodyA, Body *bodyB);

void applyVelocity(Body *body, float dt);

void applyAcceleration(Body *body, float dt);

Vector2 getCenterOfMass(const SimulationState *state);

#endif
