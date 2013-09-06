/*
 * entitylist.cpp
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */

#include "entitylist.h"

EntityList::EntityList(const EntityList &src) {
	copy(src);
}

EntityList &EntityList::operator=(const EntityList &src) {
	if (this != &src) {
		copy(src);
	}
	return *this;
}

EntityList::~EntityList() {
	destroy();
}

void EntityList::clear() {
	destroy();
}

void EntityList::add(Entity *data) {
	if (m_tail != NULL) {
		m_tail->next = new EntityNode;
		m_tail->next->data = (Entity *)data;
		m_tail->next->prev = m_tail;
		m_tail = m_tail->next;
		m_tail->next = NULL;
	}
	else {
		m_head = new EntityNode;
		m_head->data = (Entity *)data;
		m_head->next = NULL;
		m_head->prev = NULL;

		m_tail = m_head;
	}
	++m_numOfEntities;
}

void EntityList::remove(const Entity &data) {
	EntityNode *currNode = m_head;
	if (*(currNode->data) == data) {
		m_head = currNode->next;
		m_head->prev = NULL;
		delete currNode->data;
		delete currNode;
		--m_numOfEntities;
		return;
	}

	currNode = m_tail;

	if (*(currNode->data) == data) {
		m_tail = currNode->prev;
		m_tail->next = NULL;
		delete currNode->data;
		delete currNode;
		--m_numOfEntities;
		return;
	}

	currNode = m_head;

	while (currNode != NULL) {
		if (*(currNode->data) == data) {
			currNode->prev->next = currNode->next;
			currNode->next->prev = currNode->prev;
			delete currNode->data;
			delete currNode;
			--m_numOfEntities;
			return;

		} else {
			currNode = currNode->next;
		}
	}
}

void EntityList::destroy() {
	EntityNode *currNode = m_head;
	EntityNode *prevNode;

	while (currNode != NULL) {
		prevNode = currNode;
		currNode = currNode->next;

		delete prevNode->data;
		delete prevNode;
	}

	m_head = NULL;
	m_tail = NULL;
	m_numOfEntities = 0;
}

void EntityList::copy(const EntityList &src) {
	destroy();
	if (src.m_head != NULL) {

		m_head->data = (Entity *)src.m_head->data->clone();
		m_head->prev = NULL;
		m_head->next = NULL;

		EntityNode *currNode = src.m_head->next;
		EntityNode *prevNode = m_head;
		EntityNode *newNode;

		while (currNode != NULL) {
			newNode = new EntityNode;
			newNode->data = (Entity *)currNode->data->clone();
			newNode->prev = prevNode;
			newNode->next = NULL;
			prevNode->next = newNode;

			currNode = currNode->next;
			prevNode = newNode;
		}

		m_tail = newNode;
		m_numOfEntities = src.m_numOfEntities;
	} else {
		m_head = NULL;
		m_tail = NULL;
		m_numOfEntities = 0;
	}
}

Entity *EntityList::getByIndex(int i) {
	EntityNode *currNode = m_head;
	int j;
	if (i >= m_numOfEntities) return NULL;
	else {
		for (j = 0; j < i; ++j) {
			currNode = currNode->next;
		}
	}
	return currNode->data;
}
