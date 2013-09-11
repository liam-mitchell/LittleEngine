/*
 * entity.cpp
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */
#include "entity.h"
#include "gamestatemanager.h"
#include "exit.h"

void createMessage(char *msg);

void Entity::draw() {
	write_image_to_buffer(backgroundBuffer, m_image, m_pos.getX() - (m_image.getWidth() / 2), m_pos.getY() - (m_image.getHeight() / 2));
}

bool Entity::operator==(const Entity &src) {
	if (m_pos == src.m_pos && m_vel == src.m_vel && m_accel == src.m_accel && m_image == src.m_image)
		return true;
	else return false;
}

float Entity::stepX(float dt) {
	float pos = m_pos.getX();
	float vel = m_vel.getX();
	float accel = m_accel.getX();

	vel += m_inputvel.getX() + (accel * dt);
	pos += vel * dt;

	return pos;
}

float Entity::stepY(float dt) {
	float pos = m_pos.getY();
	float vel = m_vel.getY();
	float accel = m_accel.getY();

	vel += m_inputvel.getY() + (accel * dt);
	pos += vel * dt;

	return pos;
}

physRect Entity::getRect() {
	physRect rect;
	rect.center.x = m_pos.getX();
	rect.center.y = m_pos.getY();
	rect.xHalfwidth = (float)m_image.getWidth() / 2;
	rect.yHalfwidth = (float)m_image.getHeight() / 2;
	return rect;
}

void Entity::step(float dt) {
	rect_manifold data;

	data.rect.center.x = m_pos.getX();
	data.rect.center.y = m_pos.getY();
	data.rect.xHalfwidth = (float)m_image.getWidth() / 2;
	data.rect.yHalfwidth = (float)m_image.getHeight() / 2;

	data.x = false;
	data.y = false;
	data.other = NULL;
	data.dist = 0;

	int num = g_Entities.getNumOfEntities();
	int i;

	data.rect.center.x = stepX(dt);

	for (i = 0; i < num; ++i) {
		Entity *other = g_Entities.getByIndex(i);
		if (other) {
			physRect otherRect = other->getRect();
			if (this != other) {
				if (!(m_properties & NOCOLLIDE) && !(other->m_properties & NOCOLLIDE)) {
					if (aabbCollide(data.rect, otherRect)) {
						if (data.dist == 0 || point2dSquaredDistance(data.rect.center, otherRect.center) < pow(data.dist, 2)) {
							data.dist = point2dDistance(data.rect.center, otherRect.center);
							data.x = true;
							data.other = other;
						}
					}
				}
			}
		}
	}

	if (data.x == true) {
		if (m_vel.getX() + m_inputvel.getX() > 0)
			m_pos.setX(data.other->m_pos.getX() - (float)data.other->m_image.getWidth() / 2 - (float)m_image.getWidth() / 2);
		else
			m_pos.setX(data.other->m_pos.getX() + (float)data.other->m_image.getWidth() / 2 + (float)m_image.getWidth() / 2);
		m_vel.setX(0);
		m_inputvel.setX(0);
	}

	data.rect.center.x = m_pos.getX();
	data.rect.center.y = stepY(dt);

	for (i = 0; i < num; ++i) {
		Entity *other = g_Entities.getByIndex(i);
		if (other) {
			physRect otherRect = other->getRect();
			if (this != other) {
				if (!(m_properties & NOCOLLIDE) && !(other->m_properties & NOCOLLIDE)) {
					if (aabbCollide(data.rect, otherRect)) {
						if (data.dist == 0 || point2dSquaredDistance(data.rect.center, otherRect.center) < pow(data.dist, 2)) {
							data.dist = point2dDistance(data.rect.center, otherRect.center);
							data.y = true;
							data.other = other;
						}
					}
				}
			}
		}
	}
	if (data.y == true) {
		if (m_vel.getY() + m_inputvel.getY() > 0) {
			m_pos.setY(data.other->m_pos.getY() - (float)data.other->m_image.getHeight() / 2 - (float)m_image.getHeight() / 2);
			this->setCanjump(true);
		} else
			m_pos.setY(data.other->m_pos.getY() + (float)data.other->m_image.getHeight() / 2 + (float)m_image.getHeight() / 2);
		m_vel.setY(0);
		m_inputvel.setY(0);
	}

	m_vel += m_accel * dt;
	m_pos += (m_vel + m_inputvel) * dt;

	if (data.other)
		resolveCollision(data.other);
}

void Entity::resolveCollision(Entity *other) {
	if (m_properties & PLAYER) {
		if ((other->m_properties & PROJECTILE) || (other->m_properties & ENEMY)) {
			g_Entities.remove(*this);
			createMessage("You died! Press backspace to restart, or Q to quit.");
			return;
		} else if (other->m_properties & EXIT) {
			nextState = static_cast<Exit *>(other)->getNextLevel();
		}

	} else if (m_properties & PROJECTILE) {
		if (other->m_properties & PLAYER) {
			g_Entities.remove(*other);
			createMessage("You died! Press backspace to restart, or Q to quit.");
		}

		g_Entities.remove(*this);
		return;

	} else if (m_properties & ENEMY) {
		if (other->m_properties & PLAYER) {
			g_Entities.remove(*other);
			createMessage("You died! Press backspace to restart, or Q to quit.");
			return;
		}
	}
}

bool Entity::read(std::ifstream &file) {
	if (!file.is_open())
		return false;

	float x;
	float y;

	file >> std::dec >> x;
	file >> y;

	m_pos.setX(x);
	m_pos.setY(y);

	file >> x;
	file >> y;

	m_vel.setX(x);
	m_vel.setY(y);

	file >> x;
	file >> y;

	m_inputvel.setX(x);
	m_inputvel.setY(y);

	file >> x;
	file >> y;

	m_accel.setX(x);
	m_accel.setY(y);

	file >> x;
	m_properties = x;

	return true;
}

bool Entity::write(std::ofstream &file) {
	if (!file.is_open())
		return false;

	file << m_pos.getX() << ' ';
	file << m_pos.getY() << ' ';

	file << m_vel.getX() << ' ';
	file << m_vel.getY() << ' ';

	file << m_inputvel.getX() << ' ';
	file << m_inputvel.getY() << ' ';

	file << m_accel.getX() << ' ';
	file << m_accel.getY() << ' ';

	file << m_properties << ' ';

	return true;
}
