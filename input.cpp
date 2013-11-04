/*
 * input.cpp
 *
 *  Created on: 2013-07-13
 *      Author: Liam
 */

#include "input.h"

GlobalInputs gInputs;

DWORD updateInput() {
	DWORD num_events = 0;
	DWORD num_events_read = 0;
	int offsetx, offsety;
	INPUT_RECORD *eventBuffer;
	GetNumberOfConsoleInputEvents(rHnd, &num_events);

	if (num_events != 0) {
		eventBuffer = new INPUT_RECORD[num_events];
		ReadConsoleInput(rHnd, eventBuffer, num_events, &num_events_read);

		if (gInputs.R_Button == true) {
			gInputs.R_isHeld = true;
		}

		if (gInputs.L_Button == true) {
			gInputs.L_isHeld = true;
		}

		for (DWORD i = 0; i < num_events_read; ++i) {
			switch (eventBuffer[i].EventType) {
			case MOUSE_EVENT:
				offsetx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
				offsety = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
				if (eventBuffer[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
					if (gInputs.xPosAtLastLeftClick != offsetx || gInputs.yPosAtLastLeftClick != offsety) {
						gInputs.L_isHeld = false;
					}

					gInputs.xPosAtLastLeftClick = offsetx;
					gInputs.yPosAtLastLeftClick = offsety;
					gInputs.L_Button = true;
				}
				else if (eventBuffer[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
					if (gInputs.xPosAtLastRightClick != offsetx || gInputs.yPosAtLastRightClick != offsety) {
						gInputs.R_isHeld = false;
					}

					gInputs.xPosAtLastRightClick = offsetx;
					gInputs.yPosAtLastRightClick = offsety;
					gInputs.R_Button = true;
				}
				else {
					gInputs.L_Button = false;
					gInputs.R_Button = false;
					gInputs.L_isHeld = false;
					gInputs.R_isHeld = false;
				}
				break;
			case KEY_EVENT:
				if (eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						gInputs.Enter = true;
						break;
					case VK_BACK:
						gInputs.Backspace = true;
						break;
					case VK_CONTROL:
						gInputs.Control = true;
						break;
					case VK_SHIFT:
						gInputs.Shift = true;
						break;
					case VK_UP:
						gInputs.Arrow_Up = true;
						break;
					case VK_LEFT:
						gInputs.Arrow_Left = true;
						break;
					case VK_DOWN:
						gInputs.Arrow_Down = true;
						break;
					case VK_RIGHT:
						gInputs.Arrow_Right = true;
						break;
					case VK_SPACE:
						gInputs.Key_Space = true;
						break;
					case VK_A:
						gInputs.Key_A = true;
						break;
					case VK_B:
						gInputs.Key_B = true;
						break;
					case VK_C:
						gInputs.Key_C = true;
						break;
					case VK_D:
						gInputs.Key_D = true;
						break;
					case VK_E:
						gInputs.Key_E = true;
						break;
					case VK_F:
						gInputs.Key_F = true;
						break;
					case VK_G:
						gInputs.Key_G = true;
						break;
					case VK_H:
						gInputs.Key_H = true;
						break;
					case VK_I:
						gInputs.Key_I = true;
						break;
					case VK_J:
						gInputs.Key_J = true;
						break;
					case VK_K:
						gInputs.Key_K = true;
						break;
					case VK_L:
						gInputs.Key_L = true;
						break;
					case VK_M:
						gInputs.Key_M = true;
						break;
					case VK_N:
						gInputs.Key_N = true;
						break;
					case VK_O:
						gInputs.Key_O = true;
						break;
					case VK_P:
						gInputs.Key_P = true;
						break;
					case VK_Q:
						gInputs.Key_Q = true;
						break;
					case VK_R:
						gInputs.Key_R = true;
						break;
					case VK_S:
						gInputs.Key_S = true;
						break;
					case VK_T:
						gInputs.Key_T = true;
						break;
					case VK_U:
						gInputs.Key_U = true;
						break;
					case VK_V:
						gInputs.Key_V = true;
						break;
					case VK_W:
						gInputs.Key_W = true;
						break;
					case VK_X:
						gInputs.Key_X = true;
						break;
					case VK_Y:
						gInputs.Key_Y = true;
						break;
					case VK_Z:
						gInputs.Key_Z = true;
						break;
					case VK_0:
						gInputs.Key_0 = true;
						break;
					case VK_1:
						gInputs.Key_1 = true;
						break;
					case VK_2:
						gInputs.Key_2 = true;
						break;
					case VK_3:
						gInputs.Key_3 = true;
						break;
					case VK_4:
						gInputs.Key_4 = true;
						break;
					case VK_5:
						gInputs.Key_5 = true;
						break;
					case VK_6:
						gInputs.Key_6 = true;
						break;
					case VK_7:
						gInputs.Key_7 = true;
						break;
					case VK_8:
						gInputs.Key_8 = true;
						break;
					case VK_9:
						gInputs.Key_9 = true;
						break;
					}
				}
				else {
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						gInputs.Enter = false;
						break;
					case VK_BACK:
						gInputs.Backspace = false;
						break;
					case VK_CONTROL:
						gInputs.Control = false;
						break;
					case VK_SHIFT:
						gInputs.Shift = false;
						break;
					case VK_UP:
						gInputs.Arrow_Up = false;
						break;
					case VK_LEFT:
						gInputs.Arrow_Left = false;
						break;
					case VK_DOWN:
						gInputs.Arrow_Down = false;
						break;
					case VK_RIGHT:
						gInputs.Arrow_Right = false;
						break;
					case VK_SPACE:
						gInputs.Key_Space = false;
					  break;
					case VK_A:
					  gInputs.Key_A = false;
					  break;
					case VK_B:
					  gInputs.Key_B = false;
					  break;
					case VK_C:
					  gInputs.Key_C = false;
					  break;
					case VK_D:
					  gInputs.Key_D = false;
					  break;
					case VK_E:
					  gInputs.Key_E = false;
					  break;
					case VK_F:
					  gInputs.Key_F = false;
					  break;
					case VK_G:
					  gInputs.Key_G = false;
					  break;
					case VK_H:
					  gInputs.Key_H = false;
					  break;
					case VK_I:
					  gInputs.Key_I = false;
					  break;
					case VK_J:
					  gInputs.Key_J = false;
					  break;
					case VK_K:
					  gInputs.Key_K = false;
					  break;
					case VK_L:
					  gInputs.Key_L = false;
					  break;
					case VK_M:
					  gInputs.Key_M = false;
					  break;
					case VK_N:
					  gInputs.Key_N = false;
					  break;
					case VK_O:
					  gInputs.Key_O = false;
					  break;
					case VK_P:
					  gInputs.Key_P = false;
					  break;
					case VK_Q:
					  gInputs.Key_Q = false;
					  break;
					case VK_R:
					  gInputs.Key_R = false;
					  break;
					case VK_S:
					  gInputs.Key_S = false;
					  break;
					case VK_T:
					  gInputs.Key_T = false;
					  break;
					case VK_U:
					  gInputs.Key_U = false;
					  break;
					case VK_V:
					  gInputs.Key_V = false;
					  break;
					case VK_W:
					  gInputs.Key_W = false;
					  break;
					case VK_X:
					  gInputs.Key_X = false;
					  break;
					case VK_Y:
					  gInputs.Key_Y = false;
					  break;
					case VK_Z:
					  gInputs.Key_Z = false;
					  break;
					case VK_0:
					  gInputs.Key_0 = false;
					  break;
					case VK_1:
					  gInputs.Key_1 = false;
					  break;
					case VK_2:
					  gInputs.Key_2 = false;
					  break;
					case VK_3:
					  gInputs.Key_3 = false;
					  break;
					case VK_4:
					  gInputs.Key_4 = false;
					  break;
					case VK_5:
					  gInputs.Key_5 = false;
					  break;
					case VK_6:
					  gInputs.Key_6 = false;
					  break;
					case VK_7:
					  gInputs.Key_7 = false;
					  break;
					case VK_8:
					  gInputs.Key_8 = false;
					  break;
					case VK_9:
					  gInputs.Key_9 = false;
					  break;
				}
			}
			break;
			}
		}
		delete [] eventBuffer;
	}
	return num_events_read;
}
