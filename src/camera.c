#include <raylib.h>
#include "camera.h"

void userInput(SimCamera *camera) {
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		Vector2 delta = GetMouseDelta();
		camera->mouseDelta.x -= delta.x * camera->sensitivity / camera->zoom;
		camera->mouseDelta.y -= delta.y * camera->sensitivity / camera->zoom;

		camera->position.x -= delta.x * camera->sensitivity / camera->zoom;
		camera->position.y -= delta.y * camera->sensitivity / camera->zoom;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
		camera->zoom = 0.5f;
	}

	if (IsKeyPressed(KEY_SPACE)) {
		if (!camera->followCenterMass) camera->mouseDelta = (Vector2){ 0, 0 };
		camera->followCenterMass = !camera->followCenterMass;
	}

	if (camera->zoom > 0.05f || GetMouseWheelMoveV().y > 0) {
		camera->zoom += GetMouseWheelMoveV().y * camera->zoomSensitivity;;
	}

	if (IsKeyPressed(KEY_ONE)) {
		camera->followBody = !camera->followBody;	
	}

	if (IsKeyPressed(KEY_C)) {
		camera->renderCenterMass = !camera->renderCenterMass;
	}
}

Vector2 getScreenCoord(Vector2 worldCoord, const SimCamera *camera) {
	float screenX = (worldCoord.x - camera->position.x) * camera->zoom + camera->offset.x;
	float screenY = (worldCoord.y - camera->position.y) * camera->zoom + camera->offset.y;

	return (Vector2){ screenX, screenY };
}

SimCamera initializeCamera() {
	SimCamera camera = {
		.followCenterMass = true,
		.renderCenterMass = false,
		.sensitivity = 1.0f,
		.zoomSensitivity = 0.05f,
		.position = (Vector2){ (float)GetScreenWidth(), (float)GetScreenHeight()/2 },
		.offset = (Vector2){ (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 },
		.zoom = 0.5f
	};

	return camera;
}
