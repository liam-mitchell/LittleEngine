/*
 * rocket.h
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#ifndef ROCKET_H_
#define ROCKET_H_

#include "entity.h"
#include "observer.h"
#include "entitycreator.h"

typedef class Rocket: public Entity, public Observer {
public:
	Rocket();
	Rocket(const vec2d &pos, const vec2d &direction);
	void update(float dt);

	virtual Rocket *clone() {return new Rocket(*this);}
private:
	vec2d m_direction;

	void fillImage();
} Rocket;

typedef class _RocketCreator: public EntityCreator {
	virtual ~_RocketCreator() {};
	virtual Entity *create(const vec2d &pos, const vec2d &dir, const int &dummy) const;
} Rocket_Creator;

#endif /* ROCKET_H_ */
