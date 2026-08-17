#ifndef CAMERA_H
#define CAMERA_H
#include <raylib.h>
#include <stdbool.h>

typedef struct {
	Vector2 position;
	Vector2 offset;
	float zoom;
	bool renderCenterMass;
	bool followCenterMass;
	float sensitivity;
	Vector2 mouseDelta;
	float zoomSensitivity;
	bool followBody;
	int targetBody;
} SimCamera;

void userInput(SimCamera *camera);

Vector2 getScreenCoord(Vector2 worldCoord, const SimCamera *camera);

SimCamera initializeCamera();

#endif
