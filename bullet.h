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

	void update(float dt);

	virtual bool write(std::ofstream &file);
	virtual bool read(std::ifstream &file);
private:
	void fillImage();

	float m_timer;
} Bullet;

typedef class _BulletCreator: public EntityCreator {
public:
	virtual ~_BulletCreator() {}
	virtual Entity *create() const {return new Bullet;}
	virtual Entity *create(const vec2d &pos, const vec2d &vel, const int &dummy) const;
} Bullet_Creator;

#endif /* BULLET_H_ */
