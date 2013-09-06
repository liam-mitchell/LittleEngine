/*
 * level2.cpp
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#include "level2.h"
#include "entityfactory.h"
#include "camera.h"
#include "properties.h"
#include "entitymanager.h"
#include "player.h"

void level2Load() {
//	g_PlayerImage = {RECTW, RECTH, WhtRectangle.chars, WhtRectangle.colours};
//	g_Player = {{1.5, HEIGHT - 1.5}, {0, 0}, {0, 0}, g_PlayerImage};
	g_pPlayer = static_cast<Player *>(g_Factory.createEntity(PLAYERCREATOR, {1.5, HEIGHT - 1.5}, {0, 0}, 0));
//	g_Entities.add(g_pPlayer);
}

void level2Initialize() {
	InitFrameRateController();
	startFrame(frameStartTime);
	g_Camera.initCamera({WIDTH / 2, HEIGHT / 2}, g_pPlayer);

	writeBackground(consoleBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void level2Update() {
	float dt = dtCalc();
	updateInput();
	updateEntities(dt);
	stepEntities(dt);
	g_Camera.update();
}

void level2Draw() {
	writeBackground(backgroundBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void level2Free() {

}

void level2Unload() {
	g_Entities.clear();
	g_Camera.resetCamera();
}
