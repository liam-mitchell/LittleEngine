/*
 * bullet.cpp
 *
 *  Created on: 2013-09-01
 *      Author: Liam
 */

#include "bullet.h"
#include "properties.h"

Bullet::Bullet():m_timer(0) {
	fillImage();
	m_inputvel.setX(BULLET_SPEED);
	m_properties = PROJECTILE;
}

Bullet::Bullet(const vec2d &pos, const vec2d &vel):m_timer(0) {
	fillImage();
	m_pos = pos;
	m_inputvel = vel;
	m_properties = PROJECTILE;
}

void Bullet::update(float dt) {
	m_timer += dt;

	if (m_timer > 10)
		g_Entities.remove(*this);
}

bool Bullet::write(std::ofstream &file) {
	if (file.is_open()) {
		int id = BULLETCREATOR;
		file << std::dec << id << ' ';

		Entity::write(file);

		file << m_timer << std::endl;

		return true;
	} else return false;
}

bool Bullet::read(std::ifstream &file) {
	if (file.is_open()) {
		Entity::read(file);

		file >> std::dec >> m_timer;

		return true;
	} else return false;
}

void Bullet::fillImage() {
	CHAR chars[1];
	COL colours[1];

	chars[0] = 248;
	colours[0] = 12 | BACKGROUND_BLUE;

	Image image(1, 1, chars, colours);
	setImage(image);
}

Entity *_BulletCreator::create(const vec2d &pos, const vec2d &vel, const int &dummy) const {
	return new Bullet(pos, vel);
}
