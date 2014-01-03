/*
 * animation.h
 *
 *  Created on: 2013-11-03
 *      Author: Liam
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "shapes.h"

typedef class Animation {
public:
	Animation();
	Animation(Image *frames, float maxtime, int framecount);
	Animation(const Animation &src);
	Animation& operator=(const Animation &src);

	void update(float dt);
	Image &getImage();

	~Animation();
private:
	Image *m_frames;
	Image m_currentframe;
	int m_currentcount;
	float m_timer;
	float m_maxtime;
	int m_framecount;
} Animation;

extern const Animation PLAYER_LEFT_ANIMATION;
extern const Animation PLAYER_RIGHT_ANIMATION;

#endif /* ANIMATION_H_ */
