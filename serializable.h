/*
 * serializable.h
 *
 *  Created on: 2013-09-06
 *      Author: Liam
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <fstream>
#include <map>

class Entity;

typedef std::map<unsigned int, Entity *> addressMap;

class AddressTranslator {
public:
	static void AddAddress(unsigned int oldAddr, Entity *pNew);
	static Entity *FindAddress(unsigned int oldAddr);
private:
	static addressMap m_addressMap;
};

class ISerializable {
public:
	virtual ~ISerializable() {}
	virtual bool write(std::ofstream &file) = 0;
	virtual bool read(std::ifstream &file) = 0;
	virtual void fixup() = 0;
};


#endif /* SERIALIZABLE_H_ */
