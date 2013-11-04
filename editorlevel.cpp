/*
 * editorlevel.cpp
 *
 *  Created on: 2013-10-12
 *      Author: Liam
 */

#include "editorlevel.h"
#include "entitymanager.h"
#include "camera.h"

void edLevelLoad() {
	deserializeEntities("editorsavefile.txt");
}

void edLevelInitialize() {
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

void edLevelUpdate() {
	float dt = dtCalc();
	updateInput();
	updateEntities(dt);
	stepEntities(dt);
	g_Camera.update();
}

void edLevelDraw() {
	writeBackground(backgroundBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void edLevelFree() {
	g_Entities.clear();
	g_Camera.resetCamera();
}

void edLevelUnload() {}

