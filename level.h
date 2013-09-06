/*
 * level.h
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "entitymanager.h"
#include "graphics.h"
#include "player.h"
#include "console.h"

void levelLoad();
void levelInitialize();
void levelUpdate();
void levelDraw();
void levelFree();
void levelUnload();

#endif /* LEVEL_H_ */
