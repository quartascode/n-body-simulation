#ifndef RENDER_H
#define RENDER_H
#include "simulation.h"
#include "camera.h"
#include <raylib.h>

void drawBodies(const SimulationState *state, const SimCamera *camera, float accumulator);

void drawCenterOfMass(const SimulationState *state, const SimCamera *camera);

Vector2 Lerp(const Vector2 vecA, const Vector2 vecB, float t);

#endif
