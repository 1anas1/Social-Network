#pragma once
#include"UserList.h"


void input(string &s) {
	//cin.ignore(1024, '\n');
	getline(cin, s);
	//fflush(stdin);

	while (cin.fail()) {
		cout << "Wrong input ! please try again." << endl;
		cin.ignore(1024, '\n');
		cin.clear();
		getline(cin, s);
		fflush(stdin);

	}
	//cin.ignore(1024, '\n');
	//cin.clear();
}

void input(int &s) {

	cin >> s;
	while (cin.fail()) {
		cin.clear();
		cout << "Wrong input ! please try again." << endl;
		cin.ignore(std::numeric_limits<std::streamsize>::max(),  '\n');
		cin >> s;
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

