/*
 * exit.h
 *
 *  Created on: 2013-09-04
 *      Author: Liam
 */

#ifndef EXIT_H_
#define EXIT_H_

#include "gamestatemanager.h"
#include "entity.h"
#include "entitycreator.h"

typedef class Exit: public Entity {
public:
	Exit();
	Exit(const vec2d &pos, const state &nextLevel);

	state getNextLevel() {return m_nextLevel;}

	virtual bool write(std::ofstream &file);
	virtual bool read(std::ifstream &file);
private:
	void fillImage();

	state m_nextLevel;
} Exit;

typedef class _ExitCreator: public EntityCreator { //TODO: fix those goddamn class names
	virtual ~_ExitCreator() {}
	virtual Entity *create() const {return new Exit;}
	virtual Entity *create(const vec2d &pos, const vec2d &dummy, const int &state) const;
} Exit_Creator;
#endif /* EXIT_H_ */
