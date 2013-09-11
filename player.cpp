/*
 * player.cpp
 *
 *  Created on: 2013-07-13
 *      Author: Liam
 */

#include "player.h"
#include <iomanip>

Player::Player() {
	m_pos.setX(0);
	m_pos.setY(0);
	m_vel.setX(0);
	m_vel.setY(0);

	CHAR chars[9];
	COL colours[9];

	chars = {
			60, 153, 62,
			184, 215, 213,
			220, 202, 220
	};

	for (int i = 0; i < 9; ++i) {
		colours[i] = 15 | BACKGROUND_BLUE;
	}

	Image image(3, 3, chars, colours);

	m_image = image;
	m_properties = PLAYER;
	canjump = true;
}

Player::Player(const vec2d pos, const vec2d vel, const vec2d accel, const Image image) :canjump(false) {
	setPos(pos);
	setVel(vel);
	setAccel(accel); //TODO: we don't use this variable anywhere, remove from base entity class
	setImage(image);
	m_properties = PLAYER;
}

void Player::update(float dt) {
	if (gInputs.Arrow_Right) {
		m_inputvel.setX(PLAYER_LEFT_RIGHT_SPEED);
	}
	if (gInputs.Arrow_Left) {
		m_inputvel.setX(-PLAYER_LEFT_RIGHT_SPEED);
	}
	else if (!(gInputs.Arrow_Right || gInputs.Arrow_Left))
		m_inputvel.setX(0);

	if (canjump && gInputs.Arrow_Up) {
		m_vel.setY(-sqrt(2.f * GRAVITY * PLAYER_JUMP_HEIGHT));
		canjump = false;
	}

	vec2d accel(0, GRAVITY);
	m_vel += accel * dt;


//	if (m_pos.getX() < 1.5) m_pos.setX(1.5);
	if (m_pos.getY() < 1.5) m_pos.setY(1.5);
//	if (m_pos.getX() > WIDTH - 1.5) m_pos.setX(WIDTH - 1.5);
	if (m_pos.getY() > HEIGHT - 1.5) {
		m_pos.setY(HEIGHT - 1.5);
		m_vel.setY(0);
		canjump = true;
	}
}

bool Player::write(std::ofstream &file) {
	if (!file.is_open())
		return false;

	int id = PLAYERCREATOR; //write id and old address to file first
	file << std::dec << id << ' ';
	file << std::hex << this << ' ';

	Entity::write(file); //write all basic entity data

	file << canjump << '\n'; //player-specific data

	return true;
}

bool Player::read(std::ifstream &file) {
	if (!file.is_open())
		return false;

	int i;
	unsigned int u;

	char c = ' ';

	while (c != 'x') {
		c = file.get();
	}

	file >> std::hex >> u; //read old address
	AddressTranslator::AddAddress(u, this); //add to the address table for fixup later

	Entity::read(file); //read basic entity data

	file >> canjump; //player-specific data

	return true;
}

//void Player::fixup() {}

Entity *_PlayerCreator::create(const vec2d &pos, const vec2d &dummy1, const int &dummy2) const {
	CHAR chars[9];
	COL colours[9];

	chars = {
			60, 153, 62,
			184, 215, 213,
			220, 202, 220
	};

	for (int i = 0; i < 9; ++i) {
		colours[i] = 15 | BACKGROUND_BLUE;
	}

	Image image(3, 3, chars, colours);
	return new Player(pos, {0, 0}, {0, 0}, image);
}

Player *g_pPlayer;
