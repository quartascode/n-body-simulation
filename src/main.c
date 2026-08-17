#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "simulation.h"
#include "camera.h"
#include "render.h"

int main () {
	Start();

	SimulationState state = initializeBodies();

	SimCamera camera = initializeCamera();

	float accumulator = 0.0f;
	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		Update(&state, &camera, accumulator);

		accumulator += dt;
		while (accumulator >= state.fixedTimeStep) {
			FixedUpdate(&state);
			accumulator -= state.fixedTimeStep;
		}

		BeginDrawing();
			ClearBackground(BLACK);
			drawBodies(&state, &camera, accumulator);
			if (camera.renderCenterMass) {
				drawCenterOfMass(&state, &camera);
			}

			char zoomString[20];
			snprintf(zoomString, sizeof(zoomString), "zoom: %.2f", camera.zoom);
			DrawText(zoomString, 5, 0, 24, RAYWHITE);
			DrawFPS(5, 25);
		EndDrawing();
	}

	free(state.bodies);
	CloseWindow();
	return 0;
}
