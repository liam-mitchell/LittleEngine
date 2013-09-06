/*
 * entitylist.h
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */

#ifndef ENTITYLIST_H_
#define ENTITYLIST_H_

#include "entity.h"

typedef struct EntityNode {
	Entity *data;
	EntityNode *next;
	EntityNode *prev;
} LL_EntityNode;

typedef class EntityList {
public:
	EntityList():m_head(NULL), m_tail(NULL), m_numOfEntities(0)  {}
	EntityList(const EntityList &src);
	EntityList &operator=(const EntityList &src);
	~EntityList();

	void add(Entity *data);
	void remove(const Entity &data);
	void clear();

	Entity *getByIndex(int i);
	int getNumOfEntities() {return m_numOfEntities;}
private:
	void destroy();
	void copy(const EntityList &src);
	EntityNode *m_head;
	EntityNode *m_tail;
	int m_numOfEntities;
} LL_Entity;

extern EntityList g_Entities;

#endif /* ENTITYLIST_H_ */
