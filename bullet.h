/*
 * bullet.h
 *
 *  Created on: 2013-09-01
 *      Author: Liam
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "entity.h"
#include "entitycreator.h"

#define BULLET_SPEED 15

typedef class Bullet: public Entity {
public:
	Bullet();
	Bullet(const vec2d &pos, const vec2d &vel);
	virtual Bullet *clone() {return new Bullet(*this);}

	void update(float dt);
private:
	void fillImage();

	float m_timer;
} Bullet;

typedef class _BulletCreator: public EntityCreator {
public:
	virtual ~_BulletCreator() {}
	virtual Entity *create(const vec2d &pos, const vec2d &vel, const int &dummy) const;
} Bullet_Creator;

#endif /* BULLET_H_ */
