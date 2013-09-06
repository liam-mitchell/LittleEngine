/*
 * entity.h
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "physics.h"
#include "shapes.h"
#include "graphics.h"
#include "entitylist.h"
#include "properties.h"
#include <cmath>

typedef class vec2d Vec2d;

typedef class Entity {
public:
	Entity():m_pos(), m_vel(), m_inputvel(), m_accel(), m_image(), m_properties(0) {}
	Entity(const vec2d &pos, const vec2d &vel, const vec2d &accel, const Image &image): m_pos(pos), m_vel(vel), m_inputvel(), m_accel(accel), m_image(image), m_properties(0) {}
	bool operator==(const Entity &src);
	virtual Entity *clone() = 0;
	virtual ~Entity() {}

	vec2d &getPos() {return m_pos;}
	vec2d &getVel() {return m_vel;}
	vec2d &getAccel() {return m_accel;}
	vec2d &getInputvel() {return m_inputvel;}
	Image &getImage() {return m_image;}
	int &getProperties() {return m_properties;}

	void setPos(vec2d pos) {m_pos = pos;}
	void setImage(Image image) {m_image = image;}
	void setVel(vec2d vel) {m_vel = vel;}
	void setAccel(vec2d accel) {m_accel = accel;}
	void setInputvel(vec2d inputvel) {m_inputvel = inputvel;}
	void setProperties(int p) {m_properties = p;}

	virtual void setCanjump(bool x) {}

	float stepX(float dt);
	float stepY(float dt);

	physRect getRect();

	virtual void update(float dt) {}
	virtual void draw();
	virtual void step(float dt);
protected:
	vec2d m_pos;
	vec2d m_vel;
	vec2d m_inputvel;
	vec2d m_accel;
	Image m_image;
	int m_properties;

	void resolveCollision(Entity *other);
} Entity_s;


#endif /* ENTITY_H_ */
