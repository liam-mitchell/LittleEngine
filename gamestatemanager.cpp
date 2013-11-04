/*
 * gamestatemanager.cpp
 *
 *  Created on: 2013-07-27
 *      Author: Liam
 */

#include "gamestatemanager.h"
#include "menu.h"
#include "level.h"
#include "level2.h"
#include "camera.h"
#include "editor.h"
#include "editorlevel.h"

state currentState;
state previousState;
state nextState;

void (*Load)();
void (*Initialize)();
void (*Update)();
void (*Draw)();
void (*Free)();
void (*Unload)();

void GSM_Init(state initState) {
	currentState = initState;
	nextState = initState;
	previousState = initState;
}

void GSM_Update() {
	switch(currentState) {
	case Menu:
		Load = &menuLoad;
		Initialize = &menuInitialize;
		Update = &menuUpdate;
		Draw = &menuDraw;
		Free = &menuFree;
		Unload = &menuUnload;
		break;
	case Level:
		Load = &levelLoad;
		Initialize = &levelInitialize;
		Update = &levelUpdate;
		Draw = &levelDraw;
		Free = &levelFree;
		Unload = &levelUnload;
		break;
	case Level2:
		Load = &level2Load;
		Initialize = &level2Initialize;
		Update = &level2Update;
		Draw = &level2Draw;
		Free = &level2Free;
		Unload = &level2Unload;
		break;
	case Editor:
		Load = &editorLoad;
		Initialize = &editorInitialize;
		Update = &editorUpdate;
		Draw = &editorDraw;
		Free = &editorFree;
		Unload = &editorUnload;
		break;
	case EditorLevel:
		Load = &edLevelLoad;
		Initialize = &edLevelInitialize;
		Update = &edLevelUpdate;
		Draw = &edLevelDraw;
		Free = &edLevelFree;
		Unload = &edLevelUnload;
		break;
	case Restart:
		break;
	case Quit:
		break;
	}
}

void GSM_Pause() {
	Entity *pauseMsg = createMessage("Game paused - press enter to resume, backspace to restart or Q to quit.");
	Draw();

	while(1) {
		updateInput();
		if (gInputs.Enter) {
			gInputs.Key_P = false;
			break;
		}
		else if (gInputs.Key_Q) {
			nextState = Quit;
			break;
		}
		else if (gInputs.Backspace) {
			nextState = Restart;
			break;
		}
		else if (gInputs.Key_S) {
			serializeEntities("savefile.txt");
			break;
		}
		else if (gInputs.Key_L) {
			deserializeEntities("savefile.txt");
			break;
		}
	}

	g_Entities.remove(*pauseMsg);
}

void GSM_PauseWithMsg(char *msg) {
	Entity *pauseMsg = createMessage(msg);
	Draw();

	while(1) {
		updateInput();
		if (gInputs.Key_P)
			break;
		else if (gInputs.Key_Q) {
			nextState = Quit;
			break;
		}
		else if (gInputs.Backspace) {
			nextState = Restart;
			break;
		}
	}

	g_Entities.remove(*pauseMsg);
}
