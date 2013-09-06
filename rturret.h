/*
 * rturret.h
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#ifndef RTURRET_H_
#define RTURRET_H_

#include "rocket.h"
#include "entitycreator.h"

typedef class RTurret: public Entity, public Observer {
public:
	RTurret(const vec2d &pos, const vec2d &dir);
	virtual RTurret *clone() {return new RTurret(*this);}

	virtual void update(float dt);
private:
	void fillImage();

	vec2d m_direction;
	float m_timer;
} RTurret;

typedef class _RTurretCreator: public EntityCreator {
	virtual ~_RTurretCreator() {}
	virtual Entity *create(const vec2d &pos, const vec2d &dir, const int &dummy) const;
} RTurret_Creator;

#endif /* RTURRET_H_ */
