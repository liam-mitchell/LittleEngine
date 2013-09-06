/*
 * player.h
 *
 *  Created on: 2013-07-13
 *      Author: Liam
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "graphics.h"
#include "physics.h"
#include "framerate.h"
#include "entity.h"
#include "observer.h"
#include "entitycreator.h"

#define PLAYER_LEFT_RIGHT_SPEED 30.f
#define PLAYER_JUMP_SPEED -90.f
#define PLAYER_JUMP_HEIGHT 11.5f

typedef class Player : public Entity, public Subject {
public:
	Player();
	Player(const vec2d pos, const vec2d vel, const vec2d accel, const Image image);
	virtual Player *clone() {return new Player(*this);}

	virtual void setCanjump(bool x) {canjump = x;}

	virtual void update(float dt);
private:
	bool canjump;
} Player_s;

typedef class _PlayerCreator: public EntityCreator {
	virtual ~_PlayerCreator() {}
	virtual Entity *create(const vec2d &pos, const vec2d &dummy1, const int &dummy2) const;
} Player_Creator;

extern Player *g_pPlayer;
#endif /* PLAYER_H_ */
