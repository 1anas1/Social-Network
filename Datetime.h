#pragma once
#pragma warning(disable:4996)
#include <ctime>
#include <string>
using namespace std;

static class Datetime
{
public:

	static time_t makedate(int m, int y, int d) {
		struct tm tm = { 0 };
		tm.tm_hour = 12;
		tm.tm_min = tm.tm_sec = 0;
		tm.tm_year = y - 1900;
		tm.tm_mon = m - 1;
		tm.tm_mday = d;
		tm.tm_isdst = -1;
		return mktime(&tm);
	}
	
	static string getTime(time_t t) {
		char buff[20];
		strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&t));
		return string(buff);
	}

	Datetime();
	~Datetime();
};

