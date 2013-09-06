/*
 * vec2d.h
 *
 *  Created on: 2013-07-14
 *      Author: Liam
 */

#ifndef VEC2D_H_
#define VEC2D_H_

#include <math.h>

typedef class Entity Entity_s;

typedef struct point2d {
	float x, y;
} Point2d;

typedef class vec2d {
public:
	vec2d() {point.x = 0;
				point.y = 0;}
	vec2d(float xin, float yin) {point = {xin, yin};}

	vec2d &operator+=(const vec2d &rhs);
	vec2d &operator*=(const float &f);
	vec2d &operator/=(const float &f);
	vec2d &operator-=(const vec2d &rhs);
	vec2d operator+(const vec2d &rhs);
	vec2d operator*(const float &f);
	vec2d operator/(const float &f);
	vec2d operator-(const vec2d &rhs);
	bool operator==(const vec2d &rhs);

	float getX() const {return point.x;}
	float getY() const {return point.y;}
	void setX(const float input) {point.x = input;}
	void setY(const float input) {point.y = input;}

	float distance(const vec2d &other);
	vec2d normalize() const;
private:
	point2d point;
} Vec2d;

#endif /* VEC2D_H_ */
