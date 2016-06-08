#pragma once
#include <vector>
#include "Post.h"
#include <iostream>
#include <fstream>
using namespace std;

class PostList
{
	vector<Post> list;	
public:
	PostList();
	virtual ~PostList();

	void insert(Post p) {
		list.push_back(p);
	}
	//void update(Post p) {}
	//void remove(Post p);
	//void find(Post p);

	void printLastN(int i) {
		int counter = 0;
		
		for (auto i = list.rbegin(); i != list.rend(); i++) {
			cout << counter+1 << " - " << i->getContent() << endl;
			if (counter == 3) break;
			counter++;
		}
	}

	string tostring()
	{
		string obj = "";
		for (auto i = list.begin(); i != list.end();i++)
		{
			obj += i->getContent() + ",";
		}
		obj = obj.substr(0, obj.length() - 1);
		return obj;
	}

};

