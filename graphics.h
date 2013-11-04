/*
 * graphics.h
 *
 *  Created on: 2013-07-12
 *      Author: Liam
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "console.h"
#include "shapes.h"
#include "input.h"

enum { DRAW, NODRAW, QUIT };

extern CHAR_INFO backgroundBuffer[WIDTH * HEIGHT];

void writeBackground(CHAR_INFO * buffer);
void clearBackground(CHAR_INFO *buffer);
void write_image_to_buffer(CHAR_INFO buffer[], Image &image, int x_offset, int y_offset);
int getEvents();
void copyBuffer(CHAR_INFO *buffer1, CHAR_INFO *buffer2);

#endif /* GRAPHICS_H_ */
