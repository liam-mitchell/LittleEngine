/*
 * observer.h
 *
 *  Created on: 2013-09-03
 *      Author: Liam
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <list>

class Subject;

class Observer {
public:
	Observer():m_pSubject(0) {}
	virtual ~Observer();
	void setSubject(Subject *pSubj);
protected:
	Subject *m_pSubject;
};

class Subject {
public:
	virtual ~Subject();
	virtual void addObserver(Observer *pObs);
	virtual void removeObserver(Observer *pObs);
protected:
	typedef std::list<Observer *> ObsList;
	ObsList m_observers;
};


#endif /* OBSERVER_H_ */
