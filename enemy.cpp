/*
 * enemy.cpp
 *
 *  Created on: 2013-07-28
 *      Author: Liam
 */

#include "enemy.h"

Enemy::Enemy():m_patroldist(), m_home() {
	m_properties = ENEMY;
}

Enemy::Enemy(vec2d pos, int width, int height, int patroldist):m_home(pos) {
	m_pos = pos;
	m_patroldist = patroldist;
	m_properties = ENEMY;

	CHAR chars[(int)(width * height)];
	COL colours[(int)(width * height)];

	for (int i = 0; i < (int)(width * height); ++i) {
		chars[i] = 233;
		colours[i] = 12;
	}

	Image image(width, height, chars, colours);
	m_image = image;
	m_inputvel.setX(ENEMY_PATROL_SPEED);
}

void Enemy::update(float dt) {
	if (m_pos.getX() - m_home.getX() > m_patroldist)
		m_inputvel.setX(-ENEMY_PATROL_SPEED);
	else if (m_home.getX() - m_pos.getX() > m_patroldist)
		m_inputvel.setX(ENEMY_PATROL_SPEED);

	vec2d accel(0, GRAVITY);
	m_vel += accel * dt;

	if (m_pos.getX() < m_image.getWidth()) m_pos.setX(m_image.getWidth());
	if (m_pos.getY() < m_image.getHeight()) m_pos.setY(m_image.getHeight());
	if (m_pos.getX() > WIDTH - m_image.getWidth()) m_pos.setX(WIDTH - m_image.getWidth());
	if (m_pos.getY() > HEIGHT - m_image.getHeight()) {
		m_pos.setY(HEIGHT - m_image.getHeight());
		m_vel.setY(0);
	}
}

void Enemy::resize(const int &w, const int &h) {
	CHAR chars[w * h];
	COL colours[w * h];

	for (int i = 0; i < w * h; ++i) {
		chars[i] = 233;
		colours[i] = 12;
	}

	Image image(w, h, chars, colours);
	m_image = image;
}

bool Enemy::write(std::ofstream &file) {
	if (file.is_open()) {
		int id = ENEMYCREATOR;
		file << std::dec << id << ' ';

		Entity::write(file);

		file << std::dec << m_patroldist << ' ';
		file << m_home.getX() << ' ';
		file << m_home.getY() << ' ';

		file << m_image.getWidth() << ' ';
		file << m_image.getHeight() << ' ';

		file << std::endl;
		return true;
	} else return false;
}

bool Enemy::read(std::ifstream &file) {
	if (file.is_open()) {
		float f;
		int w, h;

		Entity::read(file);

		file >> m_patroldist;

		file >> f;
		m_home.setX(f);
		file >> f;
		m_home.setY(f);

		file >> w;
		file >> h;
		resize(w, h);

		file.get();

		return true;
	} else return false;
}

Entity *_EnemyCreator::create(const vec2d &pos, const vec2d &size, const int &properties) const {
	Entity *entity = new Enemy(pos, size.getX(), size.getY(), properties);
	return entity;
}

Enemy_Creator EnemyCreator;
