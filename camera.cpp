/*
 * camera.cpp
 *
 *  Created on: 2013-08-12
 *      Author: Liam
 */

#include "camera.h"
#include "graphics.h"
#include "properties.h"
#include "entity.h"

void Camera::update() {
	if (m_pSubject == NULL) return;

	if (m_pos.getX() - WIDTH / 2 > static_cast<Player *>(m_pSubject)->getPos().getX())
		m_pos.setX(m_pos.getX() - WIDTH);
	else if (m_pos.getX() + WIDTH / 2 < static_cast<Player *>(m_pSubject)->getPos().getX())
		m_pos.setX(m_pos.getX() + WIDTH);

	if (m_pos.getY() - HEIGHT / 2 > static_cast<Player *>(m_pSubject)->getPos().getY())
		m_pos.setY(m_pos.getY() - HEIGHT);
	else if (m_pos.getY() + HEIGHT / 2 < static_cast<Player *>(m_pSubject)->getPos().getY())
		m_pos.setY(m_pos.getY() + HEIGHT);
}

void Camera::initCamera(const vec2d &pos, Player *target) {
	m_pos = pos;
	setSubject(static_cast<Subject *>(target));
}

void Camera::resetCamera() {
	setSubject(NULL);
}

void Camera::renderEntity(Entity *pEntity) {
	int x, y, xPos, yPos;

	float camx = m_pos.getX();
	float camy = m_pos.getY();

	Image &image = pEntity->getImage();

	int width = image.getWidth();
	int height = image.getHeight();
	CHAR *chars = image.getChars();
	COL *colours = image.getColours();

	float xoffset = pEntity->getPos().getX() - camx - width / 2.f;
	float yoffset = pEntity->getPos().getY() - camy - height / 2.f;

	for (y = 0; y < height; ++y) {
		for (x = 0; x < width; ++x) {
			if (chars[x + width * y] != 255 && boundCheck(camx + xoffset + x, camy + yoffset + y)) {
					xPos = WIDTH / 2 + xoffset + x;
					yPos = HEIGHT / 2 + yoffset + y;

					backgroundBuffer[xPos + WIDTH * yPos].Char.AsciiChar = chars[x + width * y];
					backgroundBuffer[xPos + WIDTH * yPos].Attributes = colours[x + width * y];
			}
		}
	}
}


bool Camera::boundCheck(int x, int y) {
	if (x < m_pos.getX() - WIDTH / 2 || x >= m_pos.getX() + WIDTH / 2)
		return false;
	if (y < m_pos.getY() - HEIGHT / 2 || y >= m_pos.getY() + HEIGHT / 2)
		return false;
	return true;
}

Camera g_Camera;
