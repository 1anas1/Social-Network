#pragma once
#include <time.h>
#include <iostream>
#include <string>
#include "Datetime.h"
using namespace std;

class Event
{
	time_t t;
	string description;

public:
	Event(time_t t, string description) {
		this->t = t;
		this->description = description;
	}
	void print() {
		cout << Datetime::getTime(t) << "  -  " << description << endl;
	}
	time_t getTime() {
		return t;
	}
	time_t getTime() const {
		return t;
	}
	string getDesription()
	{
		return description;
	}
	virtual ~Event() {}
};

