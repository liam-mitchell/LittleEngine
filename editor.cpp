/*
 * editor.cpp
 *
 *  Created on: 2013-10-06
 *      Author: Liam
 */

#include "editor.h"
#include "camera.h"
#include "input.h"
#include "entitymanager.h"
#include "properties.h"
#include "player.h"
#include <math.h>

#define EDITOR_CAM_SPEED 15

int creatorID;

void editorLoad() {}

void editorInitialize() {
	InitFrameRateController();
	startFrame(frameStartTime);

	g_Camera.initCamera({WIDTH / 2, HEIGHT / 2}, NULL);

//	writeBackground(consoleBuffer);
	clearBackground(consoleBuffer);
	drawEntities();
	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void editorUpdate() {
	float dt = dtCalc();
	updateInput();

//	gInputs.Key_1 = true;

	if (gInputs.Key_0)
		creatorID = PLAYERCREATOR;
	else if (gInputs.Key_1)
		creatorID = TILECREATOR;
	else if (gInputs.Key_2)
		creatorID = ENEMYCREATOR;
	else if (gInputs.Key_3)
		creatorID = TURRETCREATOR;
	else if (gInputs.Key_4)
		creatorID = RTURRETCREATOR;
	else if (gInputs.Key_5)
		creatorID = EXITCREATOR;

	vec2d vel(0, 0);

	if (gInputs.Arrow_Up) {
		vel.setY(-EDITOR_CAM_SPEED);
		g_Camera.move(vel * dt);
		return;
	} else if (gInputs.Arrow_Down) {
		vel.setY(EDITOR_CAM_SPEED);
		g_Camera.move(vel * dt);
		return;
	}

	if (gInputs.Arrow_Left) {
		vel.setX(-EDITOR_CAM_SPEED);
		g_Camera.move(vel * dt);
		return;
	} else if (gInputs.Arrow_Right) {
		vel.setX(EDITOR_CAM_SPEED);
		g_Camera.move(vel * dt);
		return;
	}

//	gInputs.Key_L = true;

	if (gInputs.L_Button && !gInputs.L_isHeld) {
		vec2d pos(gInputs.xPosAtLastLeftClick + g_Camera.getPos().getX() - WIDTH / 2 + 1, gInputs.yPosAtLastLeftClick + g_Camera.getPos().getY() - HEIGHT / 2 + 1);
		int num = g_Entities.getNumOfEntities();
		int i;
		for (i = 0; i < num; ++i) {
			Entity *entity = g_Entities.getByIndex(i);
			if ( pointRectCollide(pos, entity->getRect()) ) {
				entity->rotate();
				break;
			}
		}

		if (i == num) {
			switch(creatorID) {
			case PLAYERCREATOR:
				g_pPlayer = static_cast<Player *>(g_Factory.createEntity(creatorID, pos, {0, 0}, 0));
				break;
			case TILECREATOR:
				g_Factory.createEntity(creatorID, pos, {1, 1}, 0);
				break;
			case ENEMYCREATOR:
				g_Factory.createEntity(creatorID, pos, {1, 1}, 5);
				break;
			case TURRETCREATOR:
				g_Factory.createEntity(creatorID, pos, {1, 0}, 0);
				break;
			case EXITCREATOR:
				g_Factory.createEntity(creatorID, pos, {0, 0}, Menu);
				break;
			case RTURRETCREATOR:
				RTurret *pRTurret = static_cast<RTurret *>(g_Factory.createEntity(creatorID, pos, {1, 0}, 0));
				pRTurret->setSubject(g_pPlayer);
				break;
			}

		}

	}

	if (gInputs.R_Button && !gInputs.R_isHeld) {
		vec2d pos(gInputs.xPosAtLastRightClick + 1, gInputs.yPosAtLastRightClick + 1);
		int num = g_Entities.getNumOfEntities();
		int i;
		for (i = 0; i < num; ++i) {
			Entity *entity = g_Entities.getByIndex(i);
			if ( pointRectCollide(pos, entity->getRect()) ) {
				g_Entities.remove(*entity);
				break;
			}
		}
	}

	if (gInputs.Key_S) {
		serializeEntities("editorsavefile.txt");
	}

	if (gInputs.Key_L) {
		deserializeEntities("editorsavefile.txt");
	}

	if (gInputs.Key_T) {
		serializeEntities("editorsavefile.txt");
		nextState = EditorLevel;
	}
}

void editorDraw() {
	clearBackground(backgroundBuffer);
	writeBackground(backgroundBuffer);
	drawEntities();

	vec2d pos(0, 0);
	g_Camera.writeString("Welcome to the Little   |", pos);
	pos.setY(1);
	g_Camera.writeString("Engine's Level Editor!  |", pos);
	pos.setY(2);
	g_Camera.writeString("                        |", pos);
	pos.setY(3);
	g_Camera.writeString("Left click to place an  |", pos);
	pos.setY(4);
	g_Camera.writeString("entity in the level.    |", pos);
	pos.setY(5);
	g_Camera.writeString("Right click to remove an|", pos);
	pos.setY(6);
	g_Camera.writeString("entity.                 |", pos);
	pos.setY(7);
	g_Camera.writeString("                        |", pos);
	pos.setY(8);
	g_Camera.writeString("Press one of the number |", pos);
	pos.setY(9);
	g_Camera.writeString("keys to choose the type |", pos);
	pos.setY(10);
	g_Camera.writeString("of entity placed.       |", pos);
	pos.setY(11);
	g_Camera.writeString("                        |", pos);
	pos.setY(12);
	g_Camera.writeString("    0. Player           |", pos);
	pos.setY(13);
	g_Camera.writeString("    1. Tile             |", pos);
	pos.setY(14);
	g_Camera.writeString("    2. Moving enemy     |", pos);
	pos.setY(15);
	g_Camera.writeString("    3. Turret           |", pos);
	pos.setY(16);
	g_Camera.writeString("    4. Rocket Turret    |", pos);
	pos.setY(17);
	g_Camera.writeString("    5. Exit             |", pos);
	pos.setY(18);
	g_Camera.writeString("                        |", pos);
	pos.setY(19);
	g_Camera.writeString("Move the camera using   |", pos);
	pos.setY(20);
	g_Camera.writeString("the arrow keys.         |", pos);

	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void editorFree() {
	g_Entities.clear();
	g_Camera.resetCamera();
}

void editorUnload() {}
