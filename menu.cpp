/*
 * menu.cpp
 *
 *  Created on: 2013-09-28
 *      Author: Liam
 */

#include "menu.h"
#include "camera.h"
#include "gamestatemanager.h"
#include "input.h"

void menuLoad() {}

void menuInitialize() {
	InitFrameRateController();
	startFrame(frameStartTime);
	g_Camera.initCamera({WIDTH / 2, HEIGHT / 2}, NULL);
}

void menuUpdate() {
	dtCalc();
	updateInput();

	if (gInputs.Key_P) {
		nextState = Level;
		gInputs.Key_P = false;
	} else if (gInputs.Key_E) {
		nextState = Editor;
	} else if (gInputs.Key_Q) {
		nextState = Quit;
	}
}

void menuDraw() {
	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
		backgroundBuffer[i].Char.AsciiChar = ' ';
		backgroundBuffer[i].Attributes = 0;
	}
	vec2d pos(0, 0);
	g_Camera.writeString("Welcome to the Little Engine That Could!", pos);

	pos.setY(2);
	g_Camera.writeString("Please choose from the following options: ", pos);

	pos.setY(4);
	g_Camera.writeString("	P: Play the game", pos);

	pos.setY(5);
	g_Camera.writeString("	E: Enter the level editor", pos);

	pos.setY(6);
	g_Camera.writeString("	Q: Quit the engine demo", pos);

	pos.setY(8);
	g_Camera.writeString("Press escape to return to this menu at any time.", pos);

	copyBuffer(consoleBuffer, backgroundBuffer);
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}

void menuFree() {
	g_Camera.resetCamera();
}

void menuUnload() {}
