#include <raylib.h>
#include "camera.h"
#include "simulation.h"
#include "physics.h"

Vector2 Lerp(const Vector2 vecA, const Vector2 vecB, float t) {
	Vector2 result;
	result.x = vecA.x + (vecB.x - vecA.x) * t;
	result.y = vecA.y + (vecB.y - vecA.y) * t;

	return result;
}

void drawBodies(const SimulationState *state, const SimCamera *camera) {
	for (int i = 0; i < state->bodyCount; i++) {
		Vector2 bodyPos = state->bodies[i].lerpedPos;

		Vector2 screenCoord = getScreenCoord(bodyPos, camera);
		DrawCircle(screenCoord.x, screenCoord.y, state->bodies[i].radius * camera->zoom * 2, state->bodies[i].color);
	}
}

void drawCenterOfMass(const SimulationState *state, const SimCamera *camera) {
	Vector2 screenCoord = getScreenCoord(getCenterOfMass(state), camera);
	DrawCircle(screenCoord.x, screenCoord.y, 2 * camera->zoom, GRAY);
}



