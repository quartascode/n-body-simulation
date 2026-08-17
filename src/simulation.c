#include "simulation.h"
#include <raylib.h>
#include <stdlib.h>
#include "body.h"
#include "physics.h"
#include "camera.h"
#include "render.h"


void Start () {
	int screenWidth = 1920;
	int screenHeight = 1080;

	SetTargetFPS(180);
	InitWindow(screenWidth, screenHeight, "n body simulation");
}

void FixedUpdate(SimulationState *state) {
	for (int i = 0; i < state->bodyCount; i++) {
		resetBodyAcceleration(&state->bodies[i]);
	}

	for (int i = 0; i < state->bodyCount; i++) {
		for (int j = i+1; j < state->bodyCount; j++) {
			applyGravityForBodyPair(state, &state->bodies[i], &state->bodies[j]);
		}
	}

	for (int i = 0; i < state->bodyCount; i++) {
		applyAcceleration(&state->bodies[i], state->fixedTimeStep);
		applyVelocity(&state->bodies[i], state->fixedTimeStep);
	}
}

void Update (SimulationState *state, SimCamera *camera, float accumulator) {
	if (camera->followCenterMass) {
		Vector2 centerOfMass = getCenterOfMass(state);
		camera->position.x = centerOfMass.x + camera->mouseDelta.x * camera->sensitivity;
		camera->position.y = centerOfMass.y + camera->mouseDelta.y * camera->sensitivity;
	}

	if (camera->followBody) {
		if (IsKeyPressed(KEY_RIGHT) && camera->targetBody < state->bodyCount - 1) {
			camera->targetBody++;
		}
		if (IsKeyPressed(KEY_LEFT) && camera->targetBody > 0) {
			camera->targetBody--;
		}
		camera->position = state->bodies[camera->targetBody].lerpedPos;
	}

	float alpha = accumulator / state->fixedTimeStep;
	for (int i = 0; i < state->bodyCount; i++) {
		state->bodies[i].lerpedPos = Lerp(state->bodies[i].lastPosition, state->bodies[i].position, alpha);
	}

	userInput(camera);
}

SimulationState initializeBodies() {
    int count = 6;

    Body *bodies = malloc(count * sizeof(Body));
    if (!bodies) {
        exit(1);
    }

	bodies[0] = (Body) {
		.position = (Vector2){ 800, 450 },
		.velocity = (Vector2){ 0, 0 },
		.mass = 900000,
		.radius = 10,
		.color = BLUE
	};
	bodies[1] = (Body) {
		.position = (Vector2){ 1500, 450 },
		.velocity = (Vector2){ GetRandomValue(-300, 300), GetRandomValue(-300, 300) },
		.mass = 1000,
		.radius = 10,
		.color = RED
	};
	bodies[2] = (Body) {
		.position = (Vector2){ 1300, 150 },
		.velocity = (Vector2){ GetRandomValue(-300, 300), GetRandomValue(-300, 300) },
		.mass = 1000,
		.radius = 10,
		.color = ORANGE
	};
	bodies[3] = (Body) {
		.position = (Vector2){ 1300, 850 },
		.velocity = (Vector2){ GetRandomValue(-300, 300), GetRandomValue(-300, 300) },
		.mass = 1000,
		.radius = 10,
		.color = PURPLE
	};
	bodies[4] = (Body) {
		.position = (Vector2){ 100, 150 },
		.velocity = (Vector2){ GetRandomValue(-300, 300), GetRandomValue(-300, 300) },
		.mass = 1000,
		.radius = 10,
		.color = YELLOW
	};
	bodies[5] = (Body) {
		.position = (Vector2){ 100, 850 },
		.velocity = (Vector2){ GetRandomValue(-300, 300), GetRandomValue(-300, 300) },
		.mass = 1000,
		.radius = 10,
		.color = DARKBLUE
	};

    SimulationState state = {
        .bodyCount = count,
        .gravitationalConstant = 100.0f,
        .bodies = bodies,
		.fixedTimeStep = 1.0f/120.0f,
    };

	return state;
}
