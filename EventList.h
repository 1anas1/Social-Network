#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

#include "Event.h"
using namespace std;

struct EventLess : public binary_function <Event * , Event * , bool>
{
	bool operator ()(const Event * lhs, Event * rhs) const
	{
		return lhs->getTime() < rhs->getTime();
	}
};


class EventList
{
	priority_queue<Event *, std::vector<Event* >, EventLess > * p;
public:
	EventList() {
		p = new priority_queue<Event *, std::vector<Event* >, EventLess >();
	}
	void insert(time_t t, string desc) {
		this->p->push(new Event(t, desc));
	}

	priority_queue<Event *, std::vector<Event* >, EventLess > * clone() {
		auto * t = new priority_queue<Event *, std::vector<Event* >, EventLess >(*p);
		return t;
	}

	void periodicRemove() {
		time_t now;
		time(&now);

		while (difftime(now, p->top()->getTime()) < 0) {
			p->pop();
		}
	}
	
	string tostring()
	{
		string obj = "";
		while (!p->empty())
		{
			char buff[256];
			_ltoa_s((p->top())->getTime(), buff, 10);
			obj += string(buff);
			obj += ",";
			obj += (p->top()->getDesription());
			obj += ":";
			p->pop();
		}
		return obj;
	}
	void printLastN(int i) {
		int n = 0;
		auto t = priority_queue<Event *, std::vector<Event* >, EventLess >(*p);
		while (!t.empty()) {
			t.top()->print();
			t.pop();
			if (n++ == i) break;
		}
	}
	virtual ~EventList();
};

