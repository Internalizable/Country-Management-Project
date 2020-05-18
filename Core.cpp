#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "sha256.h"
#include "DataTypes.h"

using namespace std;

const int LOGIN_MAX_ROWS = 50, LOGIN_MAX_COLUMNS = 2;
void getStartupConfigurations(string login[][LOGIN_MAX_COLUMNS], int userAmount);

/*
 * Checks if the given user values by the user exists in the file, saved to a 2D array
 * @param usernameHashed, passwordHashed, dataList, numberOfUsers
*/
bool doesUserExist(string usernameHashed, string passwordHashed, string dataList[][LOGIN_MAX_COLUMNS], int numberOfUsers)
{
	for (int i = 0; i < numberOfUsers; i++)
	{
		if (dataList[i][0] == usernameHashed && dataList[i][1] == passwordHashed)
			return true;
	}

	return false;
}


/*
 * Main function, verifies login information and reads information from the file and saves it to a 2D array.
*/
int main()
{
	string logins[LOGIN_MAX_ROWS][LOGIN_MAX_COLUMNS];
	int count = 0;

	ifstream readLogin;
	string currentUsername, currentPassword;

	if (filesystem::create_directory("data"))
		cout << "MANAGEMENT: Succesfully created data directory!" << endl << endl;

	readLogin.open("data\\login.txt");

	cout << "\t***********************************************************" << endl;
	cout << "\a\t      Public Innovations Management - Authentication Login" << endl;
	cout << "\t***********************************************************" << endl << endl;

	if (readLogin.fail() || readLogin.peek() == ifstream::traits_type::eof()) {
		ofstream writeLogin;
		writeLogin.open("data\\login.txt");

		cout << "First login detected, welcome! Please create login details below:" << endl;

		cout << "Please input the username: ";
		getline(cin, currentUsername);

		cout << "Please input the password: ";
		getline(cin, currentPassword);

		writeLogin << sha256(currentUsername) << "\t" << sha256(currentPassword) << endl;

		logins[count][0] = sha256(currentUsername);
		logins[count][1] = sha256(currentPassword);

		count++;
		cout << endl;
	}
	else
	{

		string currentLine, trueUsername, truePassword;

		while (getline(readLogin, currentLine))
		{
			stringstream ss(currentLine);
			getline(ss, trueUsername, '\t');
			getline(ss, truePassword, '\t');

			logins[count][0] = trueUsername;
			logins[count][1] = truePassword;

			count++;
		}

		cout << "Please input the username: ";
		getline(cin, currentUsername);

		cout << "Please input the password: ";
		getline(cin, currentPassword);

		cout << endl;

		while (!doesUserExist(sha256(currentUsername), sha256(currentPassword), logins, count))
		{
			cout << "\aIncorrect username or password; please try again!" << endl;

			cout << "Please input the username: ";
			getline(cin, currentUsername);

			cout << "Please input the password: ";
			getline(cin, currentPassword);

			cout << endl;
		}

	}


	getStartupConfigurations(logins, count);
}