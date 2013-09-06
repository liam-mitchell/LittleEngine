/*
 * vec2d.cpp
 *
 *  Created on: 2013-07-14
 *      Author: Liam
 */
#include "vec2d.h"


vec2d &vec2d::operator+=(const vec2d &rhs) {
	point.x += rhs.point.x;
	point.y += rhs.point.y;
	return *this;
}

vec2d &vec2d::operator*=(const float &f) {
	point.x *= f;
	point.y *= f;
	return *this;
}

vec2d &vec2d::operator/=(const float &f) {
	point.x /= f;
	point.y /= f;
	return *this;
}

vec2d &vec2d::operator-=(const vec2d &rhs) {
	point.x -= rhs.point.x;
	point.y -= rhs.point.y;
	return *this;
}

vec2d vec2d::operator+(const vec2d &rhs) {
	vec2d vector;
	vector.point.x = this->point.x + rhs.point.x;
	vector.point.y = this->point.y + rhs.point.y;
	return vector;
}

vec2d vec2d::operator*(const float &f) {
	vec2d vector;
	vector.point.x = this->point.x * f;
	vector.point.y = this->point.y * f;
	return vector;
}

vec2d vec2d::operator/(const float &f) {
	vec2d vector;
	vector.point.x = this->point.x / f;
	vector.point.y = this->point.y / f;
	return vector;
}

vec2d vec2d::operator-(const vec2d &rhs) {
	vec2d vector;
	vector.point.x = this->point.x - rhs.point.x;
	vector.point.y = this->point.y - rhs.point.y;
	return vector;
}

bool vec2d::operator==(const vec2d &rhs) {
	if (point.x == rhs.point.x && point.y == rhs.point.y) return true;
	else return false;
}

float vec2d::distance(const vec2d &other) {
	float dist;
	float xsqrd = pow(other.getX() - point.x, 2);
	float ysqrd = pow(other.getY() - point.y, 2);
	dist = sqrt(xsqrd + ysqrd);
	return dist;
}

vec2d vec2d::normalize() const {
	vec2d v;
	float l = sqrt(pow(point.x, 2) + pow(point.y, 2));
	v.setX(point.x / l);
	v.setY(point.y / l);
	return v;
}
