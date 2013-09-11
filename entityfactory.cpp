/*
 * entityfactory.cpp
 *
 *  Created on: 2013-07-29
 *      Author: Liam
 */
#include "entityfactory.h"
#include "entitylist.h"

Entity *EntityFactory::createEntity(const int &id) {
	CreatorMap::iterator it = m_creatorMap.find(id);
	if (it == m_creatorMap.end())
		return NULL;

	EntityCreator *pCreator = it->second;
	Entity *pEntity = pCreator->create();

	g_Entities.add(pEntity);
	return pEntity;
}

Entity *EntityFactory::createEntity(const int &id, const vec2d &pos, const vec2d &size, const int &properties) {
	CreatorMap::iterator it = m_creatorMap.find(id);
	if (it == m_creatorMap.end())
		return NULL;

	EntityCreator *pCreator = it->second;
	Entity *pEntity = pCreator->create(pos, size, properties);

	g_Entities.add(pEntity);
	return pEntity;
}

bool EntityFactory::registerCreator(int id, EntityCreator *creator) {
	CreatorMap::iterator it = m_creatorMap.find(id);
	if (it != m_creatorMap.end())
		return false;

	m_creatorMap[id] = creator;
	return true;
}

EntityFactory g_Factory;

