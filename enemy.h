/*
 * enemy.h
 *
 *  Created on: 2013-07-28
 *      Author: Liam
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "entity.h"
#include "entitycreator.h"

#define ENEMY_PATROL_SPEED 15

typedef class Enemy : public Entity {
public:
	Enemy():m_patroldist(), m_home() {m_properties = ENEMY;}
	Enemy(vec2d pos, int width, int height, int patroldist);
	virtual void update(float dt);
	virtual ~Enemy() {}
	virtual Enemy *clone() {return new Enemy(*this);}
protected:
	int m_patroldist;
	vec2d m_home;
} Enemy_s;

typedef class _EnemyCreator: public EntityCreator {
public:
	virtual ~_EnemyCreator() {}
	virtual Entity *create() const {return new Enemy;}
	virtual Entity *create(const vec2d &pos, const vec2d &size, const int &properties) const;
} Enemy_Creator;

extern Enemy_Creator EnemyCreator;
#endif /* ENEMY_H_ */
