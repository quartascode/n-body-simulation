#include <math.h>
#include <raylib.h>
#include "body.h"
#include "simulation.h"

void resetBodyAcceleration(Body *body) {
	body->acceleration = (Vector2){ 0, 0 };
}

void applyGravityForBodyPair(SimulationState *state, Body *bodyA, Body *bodyB) {
	float dX = bodyB->position.x - bodyA->position.x;
	float dY = bodyB->position.y - bodyA->position.y;

	float dist = sqrt(dX * dX + dY * dY);
	if (dist < 1.0f)  dist = 1;
	

	float dirX = dX / dist;
	float dirY = dY / dist;

	float accelMagnitudeA = (state->gravitationalConstant * bodyB->mass) / (dist * dist);
    float accelMagnitudeB = (state->gravitationalConstant * bodyA->mass) / (dist * dist);

    bodyA->acceleration.x += accelMagnitudeA * dirX;
    bodyA->acceleration.y += accelMagnitudeA * dirY;

    bodyB->acceleration.x -= accelMagnitudeB * dirX;
    bodyB->acceleration.y -= accelMagnitudeB * dirY;
}

void applyVelocity(Body *body, float dt) {
	body->position.x += body->velocity.x * dt;
	body->position.y += body->velocity.y * dt;
}

void applyAcceleration(Body *body, float dt) {
	body->lastPosition = body->position;

	body->velocity.x += body->acceleration.x * dt;
	body->velocity.y += body->acceleration.y * dt;
}

Vector2 getCenterOfMass(const SimulationState *state) {
	float numeratorX = 0;
	float numeratorY = 0;
	float denominator = 0;
	for (int i = 0; i < state->bodyCount; i++) {
		numeratorX += state->bodies[i].mass * state->bodies[i].position.x;
		numeratorY += state->bodies[i].mass * state->bodies[i].position.y;

		denominator += state->bodies[i].mass;
	}

	return (Vector2){ (numeratorX / denominator), (numeratorY / denominator) };
}
