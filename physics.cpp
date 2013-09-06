/*
 * physics.cpp
 *
 *  Created on: 2013-07-23
 *      Author: Liam
 */
#include "physics.h"

float point2dDistance(point2d a, point2d b) {
	float dist;
	float xsqrd = pow(b.x - a.x, 2);
	float ysqrd = pow(b.y - a.y, 2);
	dist = sqrt(xsqrd + ysqrd);
	return dist;
}

float point2dSquaredDistance(point2d a, point2d b) {
	float dist;
	float xsqrd = pow(b.x - a.x, 2);
	float ysqrd = pow(b.y - a.y, 2);
	dist = xsqrd + ysqrd;
	return dist;
}

bool aabbCollide(physRect a, physRect b) {
	if (a.center.x + a.xHalfwidth <= b.center.x - b.xHalfwidth) return false;
	if (a.center.x - a.xHalfwidth >= b.center.x + b.xHalfwidth) return false;
	if (a.center.y + a.yHalfwidth <= b.center.y - b.yHalfwidth) return false;
	if (a.center.y - a.yHalfwidth >= b.center.y + b.yHalfwidth) return false;
	return true;
}


