/*
 * entitymanager.cpp
 *
 *  Created on: 2013-07-19
 *      Author: Liam
 */

#include "entitymanager.h"
#include "camera.h"

EntityList g_Entities;

void drawEntities() {
	int num = g_Entities.getNumOfEntities();
	for (int i = 0; i < num; ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current == NULL)
			break;
		else
			g_Camera.renderEntity(current);
	}

	if (!g_Camera.target()) g_Camera.writeString("You died! Press backspace to restart, or Q to quit.", {0, 0});
}

void updateEntities(float dt) {
	int num = g_Entities.getNumOfEntities();
	for (int i = 0; i < num; ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current == NULL)
			break;
		else
			current->update(dt);
	}
}

void stepEntities(float dt) {
	int num = g_Entities.getNumOfEntities();
	for (int i = 0; i < num; ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current == NULL)
			break;
		else
			current->step(dt);
	}
}

void registerCreators() { //TODO: put this either in the factory file or its own file
	g_Factory.registerCreator(PLAYERCREATOR, new _PlayerCreator);
	g_Factory.registerCreator(TILECREATOR, new _TileCreator);
	g_Factory.registerCreator(ENEMYCREATOR, new _EnemyCreator);
	g_Factory.registerCreator(BULLETCREATOR, new _BulletCreator);
	g_Factory.registerCreator(TURRETCREATOR, new _TurretCreator);
	g_Factory.registerCreator(ROCKETCREATOR, new _RocketCreator);
	g_Factory.registerCreator(RTURRETCREATOR, new _RTurretCreator);
	g_Factory.registerCreator(EXITCREATOR, new _ExitCreator);
}

Entity *createMessage(char *msg) {
	int width = strlen(msg);
	vec2d pos(40, 0);
	Tile *message = new Tile(80, 1, pos);
    CHAR chars[80];
    COL colours[80];

    for (int i = 0; i < 80; ++i) {
    	colours[i] = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    	chars[i] = 255;
    }

    for (int i = 0; i < width; ++i) {
    	chars[i] = msg[i];
    }

    Image image(80, 1, chars, colours);
    message->setImage(image);

    message->setProperties(NOCOLLIDE);

    g_Entities.add(message);
    return message;
}

void serializeEntities(char *filename) {
	std::ofstream file(filename);
	g_Camera.write(file);

	int num = g_Entities.getNumOfEntities();
	for (int i = 0; i < num; ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current)
			current->write(file);
		else
			break;
	}

	file.close();
}

void deserializeEntities(char *filename) {
	std::ifstream file(filename);
	g_Entities.clear();
	g_Camera.resetCamera();
	g_Camera.read(file);

	while (file.good()) {
		int id;
		file >> std::dec >> id;

		if (!file.good())
			break;

		Entity *pEntity;
		pEntity = g_Factory.createEntity(id);
		pEntity->read(file);
	}

	g_Camera.fixup();
	int num = g_Entities.getNumOfEntities();
	for (int i = 0; i < num; ++i) {
		Entity *current = g_Entities.getByIndex(i);
		if (current)
			current->fixup();
		else
			break;
	}

	file.close();
}

