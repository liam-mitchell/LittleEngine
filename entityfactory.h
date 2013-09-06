/*
 * entityfactory.h
 *
 *  Created on: 2013-07-29
 *      Author: Liam
 */

#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include "entitycreator.h"
#include "vec2d.h"
#include <map>

#define PLAYERCREATOR 1000
#define TILECREATOR 1001
#define ENEMYCREATOR 1002
#define BULLETCREATOR 1003
#define TURRETCREATOR 1004
#define ROCKETCREATOR 1005
#define RTURRETCREATOR 1006
#define EXITCREATOR 1007

class Entity;

class EntityFactory {
public:
	Entity *createEntity(const int &id, const vec2d &pos, const vec2d &size, const int &properties);
	bool registerCreator(int id, EntityCreator *creator);
private:
	typedef std::map<int, EntityCreator *> CreatorMap;
	CreatorMap m_creatorMap;
};

extern EntityFactory g_Factory;

#endif /* ENTITYFACTORY_H_ */
