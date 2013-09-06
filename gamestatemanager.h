/*
 * gamestatemanager.h
 *
 *  Created on: 2013-07-27
 *      Author: Liam
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

typedef unsigned int state;

typedef enum {
	Level,
	Level2,
	Restart,
	Quit
} stateList;

extern state currentState;
extern state previousState;
extern state nextState;

extern void (*Load)();
extern void (*Initialize)();
extern void (*Update)();
extern void (*Draw)();
extern void (*Free)();
extern void (*Unload)();

void GSM_Init(state initState);
void GSM_Update();
void GSM_Pause();
void GSM_PauseWithMsg(char *msg);


#endif /* GAMESTATEMANAGER_H_ */
