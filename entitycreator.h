/*
 * entitycreator.h
 *
 *  Created on: 2013-07-29
 *      Author: Liam
 */

#ifndef ENTITYCREATOR_H_
#define ENTITYCREATOR_H_
#include "vec2d.h"

class Entity;

typedef class EntityCreator {
public:
	virtual Entity *create(const vec2d &pos, const vec2d &size, const int &properties) const = 0;
	virtual ~EntityCreator() {}
} _EntityCreator;

#endif /* ENTITYCREATOR_H_ */
