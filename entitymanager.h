/*
 * entitymanager.h
 *
 *  Created on: 2013-07-19
 *      Author: Liam
 */

#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include "entitylist.h"
#include "graphics.h"
#include "player.h"
#include "console.h"
#include "tile.h"
#include "bullet.h"
#include "turret.h"
#include "rocket.h"
#include "rturret.h"
#include "exit.h"
#include "physics.h"
#include "properties.h"
#include "enemy.h"
#include "entitycreator.h"
#include "entityfactory.h"
#include <string.h>

void drawEntities();
void updateEntities(float dt);
void stepEntities(float dt);

void registerCreators();

Entity *createMessage(char *msg);

#endif /* ENTITYMANAGER_H_ */
