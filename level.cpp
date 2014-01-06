/*
 * level.cpp
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#include "level.h"
#include "entityfactory.h"
#include "camera.h"

void levelLoad() {
	deserializeEntities("level1.txt");
}

void levelInitialize() {
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

void levelUpdate() {
	float dt = dtCalc();
	updateInput();
	updateEntities(dt);
	stepEntities(dt);
	g_Camera.update();
}

void levelDraw() {
	writeBackground(backgroundBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void levelFree() {

}

void levelUnload() {
	g_Entities.clear();
	g_Camera.resetCamera();
}
