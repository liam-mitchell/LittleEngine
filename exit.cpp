/*
 * exit.cpp
 *
 *  Created on: 2013-09-04
 *      Author: Liam
 */

#include "exit.h"

Exit::Exit():m_nextLevel(Restart) {
	m_properties = EXIT;
	fillImage();
}

Exit::Exit(const vec2d &pos, const state &nextLevel):m_nextLevel(nextLevel) {
	m_pos = pos;
	m_properties = EXIT;
	fillImage();
}

void Exit::fillImage() {
	CHAR chars[12];
	COL colours[12];

	chars = {
			255, 205, 205, 255,
			186, 178, 178, 186,
			186, 178, 178, 186
	};

	colours = {
			0, 0, 0, 0,
			0, 15, 15, 0,
			0, 15, 15, 0
	};

	for (int i = 0; i < 12; ++i) {
		colours[i] |= BACKGROUND_BLUE;
	}

	Image image(4, 3, chars, colours);
	m_image = image;
}

Entity *_ExitCreator::create(const vec2d &pos, const vec2d &dummy, const int &state) const {
	return new Exit(pos, state);
}
