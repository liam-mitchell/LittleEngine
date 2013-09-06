/*
 * camera.h
 *
 *  Created on: 2013-08-12
 *      Author: Liam
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "vec2d.h"
#include <cstddef>
#include "observer.h"
#include "player.h"

class Entity;

typedef class Camera: public Observer {
public:
	Camera():m_pos(0,0) {}
	Camera(vec2d pos, Player *target):m_pos(pos) {static_cast<Subject *>(target)->addObserver(this);}

	void update();
	void initCamera(const vec2d &pos, Player *target);
	void resetCamera();

	void renderEntity(Entity *pEntity);
private:
	vec2d m_pos;

	bool boundCheck(int x, int y);
} Camera;

extern Camera g_Camera;


#endif /* CAMERA_H_ */
