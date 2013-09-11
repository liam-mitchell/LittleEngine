/*
 * rturret.cpp
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#include "rturret.h"
#include "entityfactory.h"
#include "player.h"

RTurret::RTurret(const vec2d &pos, const vec2d &dir):m_direction(dir.normalize()), m_timer(3) {
	m_pos = pos;
	fillImage();
}

void RTurret::update(float dt) {
	m_timer += dt;

	if (m_pSubject) {
		vec2d dir = static_cast<Player *>(m_pSubject)->getPos() - m_pos;
		m_direction = dir.normalize();
	}

	if (m_timer > 3) {
		vec2d pos;
		if (pow(m_direction.getX(), 2) > pow(m_direction.getY(), 2)) {
			if (m_direction.getX() > 0) {
				pos.setX(m_pos.getX() + 2.5);
				pos.setY(m_pos.getY());
			} else {
				pos.setX(m_pos.getX() - 2.5);
				pos.setY(m_pos.getY());
			}
		} else {
	 		if (m_direction.getY() > 0) {
	 			pos.setX(m_pos.getX());
	 			pos.setY(m_pos.getY() + 2.5);
	 		} else {
	 			pos.setX(m_pos.getX());
	 			pos.setY(m_pos.getY() - 2.5);
	 		}
		}

		Rocket *pRocket = static_cast<Rocket *>(g_Factory.createEntity(ROCKETCREATOR, pos, m_direction, 0));
		if (m_pSubject)
			pRocket->setSubject(m_pSubject);

		m_timer = 0;
	}

	fillImage();
}

void RTurret::fillImage() {
	CHAR chars[9];
	COL colours[9];

	for (int i = 0; i < 9; ++i) {
		chars[i] = 254;
		colours[i] = 12 | BACKGROUND_BLUE;
	}

	chars[0] = 201;
	chars[2] = 187;
	chars[6] = 200;
	chars[8] = 188;

	if (pow(m_direction.getX(), 2) > pow(m_direction.getY(), 2)) {
		if (m_direction.getX() > 0)
			chars[5] = 236;
		else
			chars[3] = 236;
	} else {
 		if (m_direction.getY() > 0)
 			chars[7] = 236;
 		else
 			chars[1] = 236;
	}

	Image image(3, 3, chars, colours);
	setImage(image);
}

Entity *_RTurretCreator::create(const vec2d &pos, const vec2d &dir, const int &dummy) const {
	return new RTurret(pos, dir);
}

bool RTurret::write(std::ofstream &file) {
	if (file.is_open()) {
		int id = RTURRETCREATOR;
		file << std::dec << id << ' ';

		Entity::write(file);

		file << std::hex << static_cast<Player *>(m_pSubject) << std::endl;

		return true;
	} else return false;
}

bool RTurret::read(std::ifstream &file) {
	if (file.is_open()) {
		Entity::read(file);

		unsigned int i;
		char c = ' ';

		while (c != 'x')
			c = file.get();

		file >> std::hex >> i;
		m_pSubject = (Subject *)i;

		return true;
	} else return false;
}

void RTurret::fixup() {
	Subject *pSubject = static_cast<Player *>(AddressTranslator::FindAddress((unsigned int)m_pSubject));
	setSubject(pSubject);
}
