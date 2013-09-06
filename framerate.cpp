/*
 * framerate.cpp
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#include "framerate.h"

float framerate = 1.0f / FPS_LIMIT;
float frameStartTime;
float dt, previousTime;

LARGE_INTEGER FREQUENCY;

float GetCurrentGameTime();

void startFrame(float &frameStartTime) {
	frameStartTime = GetCurrentGameTime();
	previousTime = frameStartTime;
}

float dtCalc() {
	float currentTime = GetCurrentGameTime();
	float dt = currentTime - previousTime;
	previousTime = currentTime;
	dtCap(dt);
	return dt;
}

void dtCap(float &dt) {
	if (dt > framerate)
		dt = framerate;
}

float GetCurrentGameTime() {
  LARGE_INTEGER currentTime;
  QueryPerformanceCounter( &currentTime );
  return (float)(currentTime.QuadPart) / (float)(FREQUENCY.QuadPart);
}

void InitFrameRateController() {
  framerate = (float)((int)(framerate * 1000.0f)) / 1000.0f;
  QueryPerformanceFrequency(&FREQUENCY);
}
