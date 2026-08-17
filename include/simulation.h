#ifndef SIMULATION_H
#define SIMULATION_H
#include <raylib.h>
#include "body.h"
#include "camera.h"

typedef struct {
	const int bodyCount;
	const float gravitationalConstant;
	Vector2 centerMass;
	Body *bodies;
	const float fixedTimeStep;
} SimulationState;

void Start ();

void Update (SimulationState *state, SimCamera *camera, float accumulator);

void FixedUpdate (SimulationState *state);

void Draw (const SimulationState *state, const SimCamera *camera);

SimulationState initializeBodies();

#endif
