/*
 * graphics.cpp
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#include "graphics.h"

/***************************************************************************
 * writeBackground
 *
 * draws a sun and cloud in the top left corner of a blue background into buffer
 ***************************************************************************/
void writeBackground(CHAR_INFO * buffer) {

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			buffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)219;
			buffer[x + WIDTH * y].Attributes = FOREGROUND_BLUE;
		}
	}

	Image sun_image(SUNW, SUNH, Sun.chars, Sun.colours);
	Image cloud_image(CLOUDW, CLOUDH, Cloud.chars, Cloud.colours);

	write_image_to_buffer(buffer, sun_image, 0, 0);
	write_image_to_buffer(buffer, cloud_image, 5, 5);
}

void clearBackground(CHAR_INFO *buffer) {
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			buffer[x + WIDTH * y].Char.AsciiChar = (unsigned char)219;
			buffer[x + WIDTH * y].Attributes = 0;
		}
	}
}

/***************************************************************************
 * write_image_to_buffer
 *
 * writes an image's character and color data to the buffer provided at the offset
 * provided
 ***************************************************************************/

void write_image_to_buffer(CHAR_INFO buffer[], Image &image, int x_offset, int y_offset) {
	bound_check(x_offset, y_offset, &image);
	int x, y;

	int width = image.getWidth();
	int height = image.getHeight();
	CHAR *chars = image.getChars();
	CHAR *colours = image.getColours();

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			if (chars[x + width * y] != 255) {
				buffer[(x_offset + x) + (y_offset + y) * WIDTH].Char.AsciiChar = chars[x + width * y];
				buffer[(x_offset + x) + (y_offset + y) * WIDTH].Attributes = colours[x + width * y];
			}
		}
	}

	return;
}

/***************************************************************************
 * getEvents
 *
 * gets all console events since last call, drawing objects to backgroundBuffer if
 * necessary due to events, then returns DRAW, NODRAW or QUIT depending on whether
 * or not the console window needs to be redrawn
 */

int getEvents() {
	DWORD num_events_read = 0;
	int event = NODRAW;

	num_events_read = updateInput();

	Image whtRect(RECTW, RECTH, WhtRectangle.chars, WhtRectangle.colours);
	Image bluRect(RECTW, RECTH, BluRectangle.chars, BluRectangle.colours);

	if (num_events_read != 0) {
		writeBackground(backgroundBuffer);
		if (gInputs.Backspace) {
			event = QUIT;
			return event;
		}
		if (gInputs.L_Button) {
			write_image_to_buffer(backgroundBuffer, whtRect, gInputs.xPosAtLastLeftClick - 1, gInputs.yPosAtLastLeftClick - 1);
			event = DRAW;
		}
		if (gInputs.R_Button) {
			write_image_to_buffer(backgroundBuffer, bluRect, gInputs.xPosAtLastRightClick - 1, gInputs.yPosAtLastRightClick - 1);
			event = DRAW;
		}
	}
	return event;
}

void copyBuffer(CHAR_INFO *buffer1, CHAR_INFO *buffer2) {
	for (int i = 0; i < WIDTH * HEIGHT; ++i) {
		buffer1[i] = buffer2[i];
	}
	return;
}
