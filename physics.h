/*
 * physics.h
 *
 *  Created on: 2013-07-23
 *      Author: Liam
 */

#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "vec2d.h"
#include <math.h>

#define GRAVITY 300.f

typedef struct physRect {
	point2d center;
	float xHalfwidth;
	float yHalfwidth;
} _RECT;

typedef struct rect_manifold {
	bool x;
	bool y;
	float dist;
	physRect rect;
	Entity *other;
} r_manifold;

bool pointRectCollide(vec2d a, physRect b);
bool aabbCollide(physRect a, physRect b);
float point2dDistance(point2d a, point2d b);
float point2dSquaredDistance(point2d a, point2d b);

#endif /* PHYSICS_H_ */
