/*
 * tile.h
 *
 *  Created on: 2013-07-17
 *      Author: Liam
 */

#ifndef TILE_H_
#define TILE_H_

#include "entity.h"
#include "entitycreator.h"

typedef class Tile : public Entity {
public:
	Tile():m_width(0), m_height(0), m_center({0, 0}) {}
	Tile(const float &width, const float &height, const vec2d &pos);
	Tile(const float &width, const float &height, const vec2d &pos, const int& properties);
	virtual Tile *clone() {return new Tile(*this);}

	virtual void step(float dt) {}
private: //TODO: we don't use these anywhere, get rid of them
	float m_width;
	float m_height;
	vec2d m_center;
} Tile_s;

typedef class _TileCreator: public EntityCreator {
public:
	virtual ~_TileCreator() {}
	virtual Entity *create() const {return new Tile;}
	virtual Entity *create(const vec2d &pos, const vec2d &size, const int &properties) const;
} Tile_Creator;

#endif /* TILE_H_ */
