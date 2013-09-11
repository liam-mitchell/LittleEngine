/*
 * tile.cpp
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */

#include "tile.h"

Tile::Tile(const float &width, const float &height, const vec2d &pos):m_width(width), m_height(height) {
	m_center.setX(pos.getX() - (width / 2));
	m_center.setY(pos.getY() - (height / 2));

	setPos(pos);
	setVel({0 , 0});
	setAccel({0, 0});

	CHAR chars[(int)(width * height)];
	COL colours[(int)(width * height)];

	for (int i = 0; i < (int)(width * height); ++i) {
		chars[i] = 219;
		colours[i] = 8;
	}

	Image image(width, height, chars, colours);
	setImage(image);
}

Tile::Tile(const float &width, const float &height, const vec2d &pos, const int &properties):m_width(width), m_height(height) {
	m_center.setX(pos.getX() - (width / 2));
	m_center.setY(pos.getY() - (height / 2));

	setPos(pos);
	setVel({0 , 0});
	setAccel({0, 0});

	CHAR chars[(int)(width * height)];
	COL colours[(int)(width * height)];

	m_properties = properties;

	if (m_properties & ENEMY) {
		for (int i = 0; i < (int)(width * height); ++i) {
			chars[i] = 176;
			colours[i] = 12;
		}
	} else {
		for (int i = 0; i < (int)(width * height); ++i) {
			chars[i] = 219;
			colours[i] = 8;
		}
	}
	Image image(width, height, chars, colours);
	setImage(image);
}

void Tile::resize(const int &w, const int &h) {
	CHAR chars[w * h];
	COL colours[w * h];

	if (m_properties & ENEMY) {
		for (int i = 0; i < (w * h); ++i) {
			chars[i] = 176;
			colours[i] = 12;
		}
	} else {
		for (int i = 0; i < (w * h); ++i) {
			chars[i] = 219;
			colours[i] = 8;
		}
	}

	Image image(w, h, chars, colours);
	setImage(image);
}

bool Tile::write(std::ofstream &file) {
	if (file.is_open()) {
		int id = TILECREATOR;
		file << std::dec << id << ' ';
		file << m_image.getWidth() << ' ';
		file << m_image.getHeight() << ' ';

		Entity::write(file);

		file << std::endl;
		return true;
	} else return false;
}

bool Tile::read(std::ifstream &file) {
	if (file.is_open()) {
		int w, h;
		file >> std::dec >> w;
		file >> h;

		Entity::read(file);
		file.get();

		resize(w, h);

		return true;
	} else return false;
}

Entity *_TileCreator::create(const vec2d &pos, const vec2d &size, const int &properties) const {
	Entity *entity = new Tile(size.getX(), size.getY(), pos, properties);
	return entity;
}
