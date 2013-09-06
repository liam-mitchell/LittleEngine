/*
 * rocket.cpp
 *
 *  Created on: 2013-09-02
 *      Author: Liam
 */
#include "rocket.h"
#include "player.h"

Rocket::Rocket() {
	m_properties = PROJECTILE;
	fillImage();
}

Rocket::Rocket(const vec2d &pos, const vec2d &direction):m_direction(direction.normalize()) {
	m_properties = PROJECTILE;
	m_pos = pos;
	m_inputvel = m_direction * 20;
	fillImage();
}

void Rocket::update(float dt) {
	if (m_pSubject) {
		vec2d dir = static_cast<Player *>(m_pSubject)->getPos() - m_pos;
		m_direction = dir.normalize();
	}

	m_inputvel = m_direction * 20;
}

void Rocket::fillImage() {
	CHAR chars[1];
	COL colours[1];

	chars[0] = 232;
	colours[0] = 12 | BACKGROUND_BLUE;

	Image image(1, 1, chars, colours);
	setImage(image);
}

Entity *_RocketCreator::create(const vec2d &pos, const vec2d &dir, const int &dummy) const {
	return new Rocket(pos, dir);
}
