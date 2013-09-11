/*
 * entitycreator.h
 *
 *  Created on: 2013-07-29
 *      Author: Liam
 */

#ifndef ENTITYCREATOR_H_
#define ENTITYCREATOR_H_
#include "vec2d.h"

#define PLAYERCREATOR 1000
#define TILECREATOR 1001
#define ENEMYCREATOR 1002
#define BULLETCREATOR 1003
#define TURRETCREATOR 1004
#define ROCKETCREATOR 1005
#define RTURRETCREATOR 1006
#define EXITCREATOR 1007

class Entity;

typedef class EntityCreator {
public:
	virtual Entity *create() const = 0;
	virtual Entity *create(const vec2d &pos, const vec2d &size, const int &properties) const = 0;
	virtual ~EntityCreator() {}
} _EntityCreator;

#endif /* ENTITYCREATOR_H_ */
