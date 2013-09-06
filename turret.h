/*
 * turret.h
 *
 *  Created on: 2013-09-02
 *      Author: Liam
 */

#ifndef TURRET_H_
#define TURRET_H_

#include "entity.h"
#include "entitycreator.h"

typedef class Turret: public Entity {
public:
	Turret(const vec2d &pos, const vec2d &dir);
	virtual Turret *clone() {return new Turret(*this);}

	virtual void update(float dt);
private:
	float m_timer;
	vec2d m_direction;
} Turret;

typedef class _TurretCreator: public EntityCreator {
public:
	virtual Entity *create(const vec2d &pos, const vec2d &dir, const int &dummy) const;
	virtual ~_TurretCreator() {}
} Turret_Creator;

#endif /* TURRET_H_ */
