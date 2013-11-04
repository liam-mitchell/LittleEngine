/*
 * consolepractice.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Danyl
 */

#define _WIN32_WINNT 0x0500

#include <stdlib.h>
#include <stdarg.h>
#include "graphics.h"
#include "level.h"
#include "gamestatemanager.h"

CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
CHAR_INFO backgroundBuffer[WIDTH * HEIGHT];

HANDLE wHnd;
HANDLE rHnd;

int main() {

	initializeConsole("Title!", 8, 8, L"Sunkure Font");

	registerCreators();

	GSM_Init(Menu);
	gInputs.Key_P = true;

	while (currentState != Quit) {

		if (currentState == Quit)
			break;

		if (currentState == Restart) {
			currentState = previousState;
			nextState = previousState;
		}

		else {
			GSM_Update();
		}

		Load();
		Initialize();

		while(currentState == nextState) {
			Update();

			if ((previousTime - frameStartTime) > framerate) {
				Draw();
				startFrame(frameStartTime);
			}

			if (gInputs.Backspace)
				nextState = Restart;
			if (gInputs.Key_Q)
				nextState = Quit;
			if (gInputs.Key_P)
				GSM_Pause();
		}

		Free();
		Unload();

		previousState = currentState;
		currentState = nextState;
	}

	return 0;
}
