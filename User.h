#pragma once
#include <string>
#include <iostream>
#include "EventList.h"
#include "PostList.h"
#include "AVLtree.h"

using namespace std;


class User
{
	string name;
	string email;
	string password;
	string class_year;
	EventList * el;
	PostList  * pl;
	AVLtree<string>  * fl;//String is equal to username

public:
	User() {
		this->el = new EventList();
		this->fl = new AVLtree<string> ();
		this->pl = new PostList();
	}

	string getEmail() { return email;  }
	string getPassword() { return password; }
	string getName() { return name; }
	string getClassYear() { return class_year; }


	void setEmail(string e) { this->email = e; }
	void setPassword(string p) { this->password = p; }
	void setName(string n) { this->name = n;  }
	void setClassYear(string cy) { this->class_year = cy; }
	void AddEvent(time_t t, string desc)
	{
		this->el->insert(t, desc);
	}
	void AddPost(string content)
	{
		Post p;
		p.setContent(content);
		this->pl->insert(p);
	}
	void AddFreindByEmail(string a)
	{
		this->fl->insert(a);
	}

	void print_all_friends() {
		this->fl->Print();
	}

	string getEventString()
	{
		return el->tostring();
	}

	priority_queue<Event *, std::vector<Event* >, EventLess > * getEventList()
	{
		return this->el->clone();
	}

	string getPostsString()
	{
		return pl->tostring();
	}

	string getFreindsString()
	{
		return fl->tostring();
	}


	void print_events(int i = 3) { this->el->printLastN(i);  }
	void print_posts(int i = 3) { this->pl->printLastN(i); }
	void printFriends() {
		this->fl->Print();
	}

	virtual ~User() {}
};

