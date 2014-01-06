/*
 * level2.cpp
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#include "level2.h"
#include "camera.h"
#include "entitymanager.h"

void level2Load() {
	deserializeEntities("level2.txt");
}

void level2Initialize() {
	InitFrameRateController();
	startFrame(frameStartTime);

	for (int i = 0; i < g_Entities.getNumOfEntities(); ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current->getProperties() & PLAYER) {
			g_pPlayer = static_cast<Player *>(current);
		}
	}

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
