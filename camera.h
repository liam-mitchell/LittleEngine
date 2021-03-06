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

typedef class Camera: public Observer, public ISerializable {
public:
	Camera():m_pos(0,0) {}
	Camera(vec2d pos, Player *target):m_pos(pos) {static_cast<Subject *>(target)->addObserver(this);}

	void update();
	void initCamera(const vec2d &pos, Player *target);
	void resetCamera();

	void move(vec2d dist) {m_pos += dist;}
	vec2d &getPos() {return m_pos;}

	void renderEntity(Entity *pEntity);
	void writeString(char *txt, vec2d pos);

	Entity *target() {return (Entity *)m_pSubject;}

	bool write(std::ofstream &file);
	bool read(std::ifstream &file);
	void fixup();
private:
	vec2d m_pos;

	bool boundCheck(int x, int y);
} Camera;

extern Camera g_Camera;


#endif /* CAMERA_H_ */
