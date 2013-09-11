/*
 * serializable.cpp
 *
 *  Created on: 2013-09-06
 *      Author: Liam
 */

#include "serializable.h"

addressMap AddressTranslator::m_addressMap;

void AddressTranslator::AddAddress(unsigned int oldAddr, Entity *pNew) {
	m_addressMap[oldAddr] = pNew;
}

Entity *AddressTranslator::FindAddress(unsigned int oldAddr) {
	addressMap::iterator it = m_addressMap.find(oldAddr);
	if (it == m_addressMap.end())
		return NULL;
	return it->second;
}
