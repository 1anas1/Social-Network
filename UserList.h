#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <map>
#include <algorithm>

#include "AVLtree.h"
#include "User.h"
#include <string>

using namespace std;

class UserList
{
	map<string, User> userMap;
public:
	void insert(User u) {
		pair<string, User> pair;
		pair.first = u.getEmail();
		pair.second = u;
		this->userMap.insert(pair);
	}


	void PrintUsers()
	{
		for (auto i = userMap.begin(); i != userMap.end(); i++) {
			cout << i->second.getName() << endl;
		}
	}
	void print_campus_events(int i = 5) {
		auto campus_wide_list = new priority_queue<Event *, std::vector<Event* >, EventLess >();

		for (auto & u : this->userMap) {
			auto t = u.second.getEventList();
			while (!t->empty()) {
				
				campus_wide_list->push(t->top());
				t->pop();
			}
		}

		while (!campus_wide_list->empty()) {
			campus_wide_list->top()->print();
			campus_wide_list->pop();
		}
	}
	UserList();
	bool login(string email, string pass) {
		if (userMap.find(email) == userMap.end()) {
			return false;
		}
		else {
			return (userMap[email].getPassword() == pass);
		}
			
	}
	User & getUserByEmail(string email) {
		if (email == "") throw "Empty User exception";
		if (userMap.find(email) == userMap.end()) {
			throw "User not found!";
		}
		return userMap[email];
	}


	void Write()
	{
		ofstream out;
		out.open("Data.txt");
		for (auto i = userMap.begin(); i != userMap.end(); i++)
		{
			out << i->second.getName() << endl;
			out << i->second.getEmail() << endl;
			out << i->second.getPassword() << endl;
			out << i->second.getClassYear() << endl;
			out << i->second.getEventString() << endl;
			out << i->second.getPostsString() << endl;
			out << i->second.getFreindsString() << endl;
		}
		out.close();
	}


	void Read()
	{
		ifstream in;
		in.open("Data.txt");
		time_t t;
		string name, email1, pass, cy, eventdesc, posts, freinds, time1;

		while (!in.eof())
		{
			User a;
			getline(in, name);
			getline(in, email1);
			getline(in, pass);
			getline(in, cy);
			getline(in, eventdesc);
			getline(in, posts);
			getline(in, freinds);

			a.setName(name);
			a.setEmail(email1);
			a.setPassword(pass);
			a.setClassYear(cy);


			char data[2048];
			strcpy(data, eventdesc.c_str());

			char *str = data;
			char *token = strchr(str, ':');

			while (token != NULL)
			{
				*token++ = '\0';

				char *token2 = strtok(str, ",");
				t = (time_t)atol(token2);
				token2 = strtok(NULL, ",");
				string desc(token2);
				a.AddEvent(t, desc);

				str = token;
				token = strchr(str, ':');
			}


			/// ADDING POST TO DS
			strcpy(data, posts.c_str());
			token = strtok(data, ",");

			while (token != NULL) {
				a.AddPost(string(token));
				token = strtok(NULL, ",");
			}


			/// ADDING FRIENDS TO DS
			strcpy(data, freinds.c_str());
			token = strtok(data, ",");

			while (token != NULL) {
				a.AddFreindByEmail(string(token));
				token = strtok(NULL, ",");
			}
			this->insert(a);
		}
	}
	virtual ~UserList();
};

