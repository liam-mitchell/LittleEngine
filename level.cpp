/*
 * level.cpp
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#include "level.h"
#include "entityfactory.h"
#include "properties.h"
#include "camera.h"
#include "gamestatemanager.h"

void levelLoad() {
	g_pPlayer = static_cast<Player *>(g_Factory.createEntity(PLAYERCREATOR, {1.5, HEIGHT - 1.5}, {0, 0}, 0));
	g_Factory.createEntity(TILECREATOR, {10, HEIGHT - 7.5}, {10, 5}, 0);
	g_Factory.createEntity(TILECREATOR, {7, HEIGHT - 15.5}, {6, 3}, 0);
	g_Factory.createEntity(TILECREATOR, {23, HEIGHT - 20.5}, {12, 3}, 0);
	g_Factory.createEntity(TILECREATOR, {40, HEIGHT - 22.5}, {6, 3}, 0);
	g_Factory.createEntity(TILECREATOR, {60, HEIGHT - 27.5}, {6, 3}, 0);
	g_Factory.createEntity(TILECREATOR, {-2, HEIGHT - 15}, {4, 30}, 0);
	g_Factory.createEntity(TILECREATOR, {70, HEIGHT - 35.5}, {8, 3}, 0);
	g_Factory.createEntity(TILECREATOR, {50, HEIGHT - 40}, {20, 2}, 0);
	g_Factory.createEntity(TILECREATOR, {20, HEIGHT - 38}, {20, 2}, 0);
	g_Factory.createEntity(TILECREATOR, {0, HEIGHT - 32}, {16, 4}, 0);
	g_Factory.createEntity(TILECREATOR, {-8, HEIGHT - 10}, {12, 4}, 0);
	g_Factory.createEntity(TILECREATOR, {-32, HEIGHT - 10}, {12, 4}, 0);
	g_Factory.createEntity(TILECREATOR, {-36, HEIGHT - 4}, {4, 8}, 0);

	g_Factory.createEntity(TILECREATOR, {50, HEIGHT - 29.5}, {3, 3}, ENEMY);
	g_Factory.createEntity(ENEMYCREATOR, {23, HEIGHT - 23}, {1, 1}, 6);
	g_Factory.createEntity(TURRETCREATOR, {75, HEIGHT - 1.5}, {-1, 0}, 0);
	g_Factory.createEntity(EXITCREATOR, {-6, HEIGHT - 1.5}, {0, 0}, Level2);

	RTurret *pRTurret = static_cast<RTurret *>(g_Factory.createEntity(RTURRETCREATOR, {-20, HEIGHT - 10}, {1, 0}, 0));
	pRTurret->setSubject(g_pPlayer);

	pRTurret = static_cast<RTurret *>(g_Factory.createEntity(RTURRETCREATOR, {-10, HEIGHT - 20}, {1, 0}, 0));
	pRTurret->setSubject(g_pPlayer);
}

void levelInitialize() {
	InitFrameRateController();
	startFrame(frameStartTime);

	g_Camera.initCamera({WIDTH / 2, HEIGHT / 2}, g_pPlayer);

	writeBackground(consoleBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void levelUpdate() {
	float dt = dtCalc();
	updateInput();
	gInputs.Arrow_Right = true;
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
