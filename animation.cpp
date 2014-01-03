/*
 * animation.cpp
 *
 *  Created on: 2013-11-03
 *      Author: Liam
 */

#include "animation.h"

Animation::Animation():m_frames(NULL), m_currentcount(1), m_timer(0), m_maxtime(0), m_framecount(0), m_currentframe() {}

Animation::Animation(Image *frames, float maxtime, int framecount):m_currentcount(1), m_timer(0), m_maxtime(maxtime), m_framecount(framecount) {
	m_frames = new Image[framecount];
	for (int i = 0; i < framecount; ++i) {
		m_frames[i] = frames[i];
	}

	m_currentframe = m_frames[0];
}

Animation::Animation(const Animation &src):m_currentcount(1), m_timer(0), m_maxtime(src.m_maxtime), m_framecount(src.m_framecount) {
	m_frames = new Image[m_framecount];
	for (int i = 0; i < m_framecount; ++i) {
		m_frames[i] = src.m_frames[i];
	}

	m_currentframe = m_frames[0];
}

Animation &Animation::operator=(const Animation &src) {
	m_timer = 0;
	m_maxtime = src.m_maxtime;
	m_framecount = src.m_framecount;

	if (m_frames) {
		delete [] m_frames;
	}

	m_frames = new Image[m_framecount];
	for (int i = 0; i < m_framecount; ++i) {
		m_frames[i] = src.m_frames[i];
	}

	m_currentframe = m_frames[0];
	m_currentcount = 1;

	return *this;
}

void Animation::update(float dt) {
	m_timer += dt;
	if (m_timer > m_maxtime / m_framecount) {
		m_timer = 0;
		m_currentcount += 1;

		if (m_currentcount > m_framecount) {
			m_currentcount = 1;
		}

		m_currentframe = m_frames[m_currentcount - 1];
	}
}

Image &Animation::getImage() {
	return m_currentframe;
}

Animation::~Animation() {
	if (m_frames) {
		delete [] m_frames;
	}
}

CHAR playerLeft1Chars[] = {
	255, 201, 255,
	255, 254, 255,
	98, 254, 98
};

CHAR playerLeft2Chars[] = {
	255, 201, 255,
	255, 254, 255,
	255, 98, 255
};

CHAR playerLeft3Chars[] = {
	255, 201, 255,
	255, 254, 255,
	98, 254, 98
};

CHAR playerLeft4Chars[] = {
	255, 201, 255,
	255, 254, 255,
	255, 98, 255
};

CHAR playerRight1Chars[] = {
	255, 187, 255,
	255, 254, 255,
	100, 254, 100
};

CHAR playerRight2Chars[] = {
	255, 187, 255,
	255, 254, 255,
	255, 100, 255
};

CHAR playerRight3Chars[] = {
	255, 187, 255,
	255, 254, 255,
	100, 254, 100
};

CHAR playerRight4Chars[] = {
	255, 187, 255,
	255, 254, 255,
	255, 100, 255
};

COL playerCols[] = {
		15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE,
		15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE,
		15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE, 15 | BACKGROUND_BLUE
};

Image left1(3, 3, playerLeft1Chars, playerCols);
Image left2(3, 3, playerLeft2Chars, playerCols);
Image left3(3, 3, playerLeft3Chars, playerCols);
Image left4(3, 3, playerLeft4Chars, playerCols);

Image right1(3, 3, playerRight1Chars, playerCols);
Image right2(3, 3, playerRight2Chars, playerCols);
Image right3(3, 3, playerRight3Chars, playerCols);
Image right4(3, 3, playerRight4Chars, playerCols);

Image PLAYER_LEFT_FRAMES[4] = {
		left1,
		left2,
		left3,
		left4
};

Image PLAYER_RIGHT_FRAMES[4] = {
		right1,
		right2,
		right3,
		right4
};

const Animation PLAYER_RIGHT_ANIMATION(PLAYER_RIGHT_FRAMES, .5f, 4);
const Animation PLAYER_LEFT_ANIMATION(PLAYER_LEFT_FRAMES, .5f, 4);
