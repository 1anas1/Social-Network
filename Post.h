#pragma once
#include <string>
using namespace std;
class Post
{
public:
	Post();
	virtual ~Post();
	void setContent(string s) { this->content = s; }
	string getContent() { return this->content;  }
private:
	string content;
};

