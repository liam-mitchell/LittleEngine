/*
 * input.h
 *
 *  Created on: 2013-07-13
 *      Author: Liam
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "console.h"

typedef enum _VIRTUAL_KEY
{
  VK_0 = 0x30,
  VK_1,
  VK_2,
  VK_3,
  VK_4,
  VK_5,
  VK_6,
  VK_7,
  VK_8,
  VK_9,
  VK_A = 0x41,
  VK_B,
  VK_C,
  VK_D,
  VK_E,
  VK_F,
  VK_G,
  VK_H,
  VK_I,
  VK_J,
  VK_K,
  VK_L,
  VK_M,
  VK_N,
  VK_O,
  VK_P,
  VK_Q,
  VK_R,
  VK_S,
  VK_T,
  VK_U,
  VK_V,
  VK_W,
  VK_X,
  VK_Y,
  VK_Z,
  VK_ENTER = 0x0D,
} VIRTUAL_KEY;

typedef struct {
	bool Key_A;
	bool Key_B;
	bool Key_C;
	bool Key_D;
	bool Key_E;
	bool Key_F;
	bool Key_G;
	bool Key_H;
	bool Key_I;
	bool Key_J;
	bool Key_K;
	bool Key_L;
	bool Key_M;
	bool Key_N;
	bool Key_O;
	bool Key_P;
	bool Key_Q;
	bool Key_R;
	bool Key_S;
	bool Key_T;
	bool Key_U;
	bool Key_V;
	bool Key_W;
	bool Key_X;
	bool Key_Y;
	bool Key_Z;
	bool Key_1;
	bool Key_2;
	bool Key_3;
	bool Key_4;
	bool Key_5;
	bool Key_6;
	bool Key_7;
	bool Key_8;
	bool Key_9;
	bool Key_0;
	bool Key_Space;
	bool Key_Ctrl;
	bool Key_Shift;
	bool Arrow_Up;
	bool Arrow_Left;
	bool Arrow_Down;
	bool Arrow_Right;
	bool Control;
	bool Backspace;
	bool Shift;
	bool Enter;
	bool L_Button; // Mouse
	bool R_Button; // Mouse
	int xPos; // Mouse (within window)
	int yPos; // Mouse (within window)
	int xPosAtLastLeftClick; // x position of cursor relative to draw area during last left or right click
	int yPosAtLastLeftClick; // y position of cursor relative to draw area during last left or right click
	int xPosAtLastRightClick; // x position of cursor relative to draw area during last left or right click
	int yPosAtLastRightClick; // y position of cursor relative to draw area during last left or right click
} GlobalInputs;

extern GlobalInputs gInputs;

DWORD updateInput();


#endif /* INPUT_H_ */
