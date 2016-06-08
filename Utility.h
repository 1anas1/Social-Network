#pragma once
#include<string >
#include"UserList.h"
#include"User.h"
#include"Common.h"

using namespace std;

static class Utility
{
public:

	static int logged_in;
	string static logged_in_user;
	UserList static db;


	static void signin() {
		string email, password;
		system("CLS");
		cout << "Enter Username : ";
		input(email);
		cout << "Enter Password : ";
		input(password);

		if (db.login(email, password))
		{
			logged_in_user = email;
			logged_in = 1;
			LoginArea();
		}
		else
		{
			cout << "Invalid username or passwrod !" << endl;
			system("pause");
		}

	}
	static int timeline() {
		cout << "************ -- User Posts -- **************" << endl;
		db.getUserByEmail(logged_in_user).print_posts();
		cout << "************ -- Campus Wide Events -- **************" << endl;
		db.print_campus_events();
		cout << "************ -- My Events -- **************" << endl;
		db.getUserByEmail(logged_in_user).print_events(3);
		return 0;
	}

	static int options() {
		char * list_of_options[] = {
		{"1. friend_list" },
		{"2. posts_list " },
		{"3. campus_events_list" },
		{"4. my_events_list" },
		{"5. add_post" },
		{"6. add_event" },
		{"7. search_people" },
		{"8. logout" },
		};
		cout << endl;
		cout << "**********************************************************************" << endl;
		for (int i = 0; i < 8; i++) {
			cout << list_of_options[i] << " | ";
		}
		return 0;
	}

	static void friend_list()			{ db.getUserByEmail(logged_in_user).printFriends();			 }
	static void posts_list()			{ db.getUserByEmail(logged_in_user).print_posts(3);			 }
	static void campus_events_list()	{ db.print_campus_events(5);								 }
	static void my_events_list()		{ db.getUserByEmail(logged_in_user).print_events(3);		 }
	
	static void add_post() {
		cout << "Enter Post Content >> " << endl;
		string cont;
		input(cont);
		db.getUserByEmail(logged_in_user).AddPost(cont);
		cout << "Post addedd successfully. " << endl;
	}
	static void add_event() {
		time_t t = 0;
		int err_flag = 0;
		do {
			if (err_flag) { cout << "Error in date, please try again."; }
			int y, m, d;
			cout << "Enter event month: ";
			input(m);
			cout << "Enter event day: ";
			input(d);
			cout << "Enter event year: ";
			input(y);
		
			t = Datetime::makedate(m, y, d);
			err_flag = 1;
		} while(t < 1);
		
		cout << "Enter Event Description >> " ;
		string cont;
		input(cont);
		db.getUserByEmail(logged_in_user).AddEvent(t,cont);
		cout << "Event Added successfully. " << endl;
	}
	static void search_people() {
		cout << "Enter a search word : " << endl;
		string s;
		input(s);

		cout << "Results: " << endl;
	}
	static void logout() { logged_in_user = "", logged_in = 0;  }


	static void LoginArea() {

			timeline();
			options();

			int inp;
			do {
				cout << "Enter option>> ";
				input(inp);

				switch (inp) {
				case 1:
					friend_list();
					break;
				case 2:
					posts_list();
					break;
				case 3:
					campus_events_list();
					break;
				case 4:
					my_events_list();
					break;
				case 5:
					add_post();
					break;
				case 6:
					add_event();
					break;
				case 7:
					search_people();
					break;
				case 8:
					logout();
					inp = 0;
					break;
				default:
					break;
				}

			} while (inp != 0);
		

	}
	static int menu_choice()
	{
		int choice;
		cout << "1-Login\n";
		cout << "2-SignUp\n";
		cout << "3-Terminate\n";
		cout << "Select : ";
		input(choice);
		return choice;
	}

	static void DashBoard()
	{
		db.Read(); // Read All records from database
		int choice = 1;
		while (choice != 3)
		{
			system("CLS");
			choice = menu_choice();
			switch (choice)
			{
			case 1:
				signin();
				break;
			case 2:
				signup();
				break;
			case 3:
				cout << "Exiting\n";
				break;
			default:
			break;
			}
		}


		db.Write(); // Write out records to database
	}

	static void signup() {
		string u, e, p, c;
		cout << "Enter username >> " ;
		input(u);
		cout << "Enter email    >> " ;
		input(e);
		
		// If email already exists ! 
		// Loop untill a right choice is 
		// choosen
		
		int email_already_exists = 0;
		do {
			try {
				db.getUserByEmail(e);
				email_already_exists = 1; 
				cout << "Email already exists! try again." << endl;
				cout << "(If you want to leave signup process, write q! and return.)." << endl;
				
				cout << "Enter email    >> ";
				input(e);
				if (e == "q!") { cout << "Signup unsuccessfull !";  return; }

			} catch (const char * err) {
				email_already_exists = 0;
			}

		} while (email_already_exists);

		cout << "Enter password >> " ;
		input(p);
		cout << "Enter class, year >> " ;
		input(c);
		User usr;
		
		usr.setName(u);
		usr.setEmail(e);
		usr.setPassword(p);
		usr.setClassYear(c);
		
		db.insert(usr);

		cout << "Thanks for signing up! Your account has been created."<<endl<<" Now you can login from main menu.";
		system("pause");

	}


};

string Utility::logged_in_user = "";
int Utility::logged_in = 0;
UserList Utility::db ;


