/*
 * observer.cpp
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */
#include "observer.h"

Observer::~Observer() {
	if (m_pSubject) {
		m_pSubject->removeObserver(this);
	}
}

void Observer::setSubject(Subject *pSubj) {
	m_pSubject = pSubj;

	if (m_pSubject)
		m_pSubject->addObserver(this);
}

Subject::~Subject() {
	ObsList::iterator it;
	for (it = m_observers.begin(); it != m_observers.end(); ++it) {
		(*it)->setSubject(NULL);
	}
}

void Subject::addObserver(Observer *pObs) {
	m_observers.push_back(pObs);
}

void Subject::removeObserver(Observer *pObs) {
	ObsList::iterator it;
	for (it = m_observers.begin(); it != m_observers.end(); ++it) {
		if ((*it) == pObs) {
			(*it)->setSubject(NULL);
			m_observers.erase(it);
			return;
		}
	}
}


