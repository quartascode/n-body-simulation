#ifndef BODY_H
#define BODY_H
#include <raylib.h>

typedef struct {
	Vector2 position;
	Vector2 lastPosition;
	Vector2 lerpedPos;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;
	float mass;
	Color color;
} Body;

#endif
