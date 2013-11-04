/*
 * turret.cpp
 *
 *  Created on: 2013-09-02
 *      Author: Liam
 */

#include "turret.h"
#include "entityfactory.h"

Turret::Turret() {
	fillImage();
}

Turret::Turret(const vec2d &pos, const vec2d &dir):m_timer(3), m_direction(dir) {
	m_pos = pos;
	fillImage();
}

void Turret::update(float dt) {
	m_timer += dt;
	if (m_timer > 3) {
		vec2d pos(m_pos.getX() - 3.5, m_pos.getY());
		vec2d vel(m_direction.normalize() * 15);
		g_Factory.createEntity(BULLETCREATOR, pos, vel, 0);
		m_timer = 0;
	}
}

bool Turret::write(std::ofstream &file) {
	if (file.is_open()) {
		int id = TURRETCREATOR;
		file << std::dec << id << ' ';

		Entity::write(file);

		file << m_timer << ' ';
		file << m_direction.getX() << ' ';
		file << m_direction.getY() << std::endl;
		return true;
	} else return false;
}

bool Turret::read(std::ifstream &file) {
	if (file.is_open()) {
		float f;

		Entity::read(file);

		file >> std::dec >> m_timer;

		file >> f;
		m_direction.setX(f);
		file >> f;
		m_direction.setY(f);

		fillImage();
		return true;
	} else return false;
}

void Turret::fillImage() {
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

void Turret::rotate() {
	if (m_direction.getX() == -1) {
		m_direction.setX(1);
	} else {
		m_direction.setX(-1);
	}

	fillImage();
}

Entity *_TurretCreator::create(const vec2d &pos, const vec2d &dir, const int &dummy) const {
	return new Turret(pos, dir);
}
