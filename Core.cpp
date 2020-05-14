#include <iostream>
#include <fstream>
#include <sstream>
#include "sha256.h"
#include "DataTypes.h"

using namespace std;

void getStartupConfigurations();

int main()
{
	ifstream readLogin;
	string currentUsername, currentPassword;

	readLogin.open("login.txt");

	if (readLogin.fail()) {
		ofstream writeLogin;
		writeLogin.open("login.txt");

		cout << "First login detected, welcome! Please create login details below:" << endl;

		cout << "Please input the username: ";
		getline(cin, currentUsername);

		cout << "Please input the password: ";
		cin.ignore();
		getline(cin, currentPassword);

		writeLogin << sha256(currentUsername) << "\t" << sha256(currentPassword);
	}
	else
	{

		string currentLine, trueUsername, truePassword;

		while (getline(readLogin, currentLine))
		{
			stringstream ss(currentLine);
			getline(ss, trueUsername, '\t');
			getline(ss, truePassword, '\t');
		}

		cout << "Please input the username: ";
		getline(cin, currentUsername);

		cout << "Please input the password: ";
		cin.ignore();
		getline(cin, currentPassword);

		while (sha256(currentUsername) != trueUsername || sha256(currentPassword) != truePassword)
		{
			cout << "Incorrect username or password; please try again!" << endl;

			cout << "Please input the username: ";
			getline(cin, currentUsername);

			cout << "Please input the password: ";
			cin.ignore();
			getline(cin, currentPassword);
		}

	}


	getStartupConfigurations();
}