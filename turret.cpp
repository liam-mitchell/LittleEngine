/*
 * turret.cpp
 *
 *  Created on: 2013-09-02
 *      Author: Liam
 */

#include "turret.h"
#include "entityfactory.h"

Turret::Turret(const vec2d &pos, const vec2d &dir):m_timer(3), m_direction(dir) {
	m_pos = pos;
	CHAR chars[12];
	COL colours[12];

	for (int i = 0; i < 12; ++i) {
		chars[i] = 240;
		colours[i] = 12;
	}

	if (m_direction.getX() < 0) {
		chars[0] = 255;
		chars[8] = 255;
		chars[4] = 181;
	} else {
		chars[3] = 255;
		chars[11] = 255;
		chars[7] = 198;
	}

	Image image(4, 3, chars, colours);
	m_image = image;
}

void Turret::update(float dt) {
	m_timer += dt;
	if (m_timer > 3) {
		vec2d pos(m_pos.getX() - 3.5, m_pos.getY());
		vec2d vel = m_direction.normalize() * 15;
		g_Factory.createEntity(BULLETCREATOR, pos, vel, 0);
		m_timer = 0;
	}
}

Entity *_TurretCreator::create(const vec2d &pos, const vec2d &dir, const int &dummy) const {
	return new Turret(pos, dir);
}
