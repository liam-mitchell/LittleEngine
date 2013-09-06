/*
 * framerate.h
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#ifndef FRAMERATE_H_
#define FRAMERATE_H_

#include <ctime>
#include <windows.h>

#define FPS_LIMIT 30

extern float frameStartTime;
extern float previousTime;
extern float framerate;

void startFrame(float &frameStartTime);
float dtCalc();
void dtCap(float &dt);
float getCurrentGameTime();
void InitFrameRateController();


#endif /* FRAMERATE_H_ */
