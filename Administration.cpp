#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DataTypes.h"
using namespace std;

bool doesCountryExist(int countryID, Country* T, int size);
void sortAdministrationAscending(Administration T[], int first, int last);
void displayAssessment(Assessment T);

bool doesAdministrationExist(int administrationID, Administration* T, int a, int b)
{
	int m = 0;

	sortAdministrationAscending(T, a, b);

	while (a <= b)
	{
		m = a + (b - a) / 2;

		if ((T + m)->idAdministration == administrationID)
			return true;

		if ((T + m)->idAdministration < administrationID)
			a = m + 1;
		else
			b = m - 1;
	}

	return false;

}

Administration createAdministration(Administration* T, Country* C, int TA_SIZE, int TC_SIZE)
{
	Administration administration;

	cout << "Please input the administration's ID: ";

	cin >> administration.idAdministration;

	while (doesAdministrationExist(administration.idAdministration, T, 0, TA_SIZE - 1))
	{
		cout << "\aThe entered idAdministration is not unique, please try again with a unique value: ";
		cin >> administration.idAdministration;
	}

	while (administration.idAdministration <= 0)
	{
		cout << "\aThe idAdministration field of the Administration must be equal or greater than 1, please try again: ";
		cin >> administration.idAdministration;
	}

	cout << "Please input the country's ID: ";

	cin >> administration.idCountry;

	while (!doesCountryExist(administration.idCountry, C, TC_SIZE))
	{
		cout << "\aThe idCountry field of the Administration is invalid! There's no country with that ID existent, please try again: ";
		cin >> administration.idCountry;
	}

	cout << "Please input the administration's name: ";

	cin.ignore();
	getline(cin, administration.name);


	cout << "Please input the Administration's current assessment value: ";
	cin >> administration.currentValue;

	while (administration.currentValue < 0 || administration.currentValue > 100)
	{
		cout << "\aThe value field of the Administration can't be lower than 0 or greater than 100, try again: ";
		cin >> administration.currentValue;
	}

	return administration;
}

void displayAdministration(Administration administration)
{
	cout << endl;
	cout << "Administration ID: " << administration.idAdministration << endl;
	cout << "Administration's Country ID: " << administration.idCountry << endl;
	cout << "Administration's Name: " << administration.name << endl;
	cout << "Administration's Current Value: " << administration.currentValue << endl;
	cout << endl;
}

void findAdministration(Administration* T, int size, int administrationID)
{
	for (int i = 0; i < size; i++)
	{
		if ((T + i)->idAdministration == administrationID)
		{
			displayAdministration(*(T + i));
			break;
		}
	}
}

void partitionAdministration(Administration T[], int first, int last, int& pivindex)
{
	int pivot = T[first].idAdministration, up = first, down = last;

	do {
		while (T[up].idAdministration <= pivot && up < last)
			up++; 
		while (T[down].idAdministration > pivot) 
			down--; 

		if (up < down)
		{
			Administration temp = T[up];
			T[up] = T[down];
			T[down] = temp;
		}
			
	} while (up < down);

	Administration temp = T[first];
	T[first] = T[down];
	T[down] = temp;

	pivindex = down;
}

void sortAdministrationAscending(Administration T[], int first, int last)
{
	int pivindex; 

	if (first < last) { 
		partitionAdministration(T, first, last, pivindex);
		sortAdministrationAscending(T, first, pivindex-1);
		sortAdministrationAscending(T, pivindex+1, last);
	}

}

void insertAdministration(Administration administration, Administration TA[], int& TA_SIZE)
{
	int pos = TA_SIZE;

	for (int i = TA_SIZE - 1; i >= 0; i--)
	{
		if (TA[i].idCountry == administration.idCountry)
		{
			pos = i + 1;
			break;
		}
	}

	for (int i = TA_SIZE; i > pos; i--)
		TA[i] = TA[i - 1];

	TA[pos] = administration;

	TA_SIZE++;
}

void deleteAdministration(Administration T[], int& administrationSize, int idAdmin) {

	for (int i = 0; i < administrationSize; i++)
	{
		if (T[i].idAdministration == idAdmin)
		{
			for (int j = i; j < administrationSize - 1; j++)
			{
				T[i] = T[i + 1];
			}

			administrationSize--;
		}
	}

}

int readAdministrationFromDisk(Administration administration[], Country TC[], int TC_SIZE)
{
	ifstream adminFile;
	string line;

	adminFile.open("administrations.csv");

	int count = 0;

	if (!adminFile.is_open())
	{
		cout << "File failed to open!" << endl;
		return 0;
	}

	string administrationID, countryID, name, currentValue;

	while (getline(adminFile, line))
	{
		stringstream ss(line);

		getline(ss, administrationID, ',');
		getline(ss, countryID, ',');
		getline(ss, name, ',');
		getline(ss, currentValue, ',');
		
		try {

			if (doesCountryExist(stoi(countryID), TC, TC_SIZE)
				&& stoi(currentValue) >= 0 && stoi(currentValue) <= 100)
			{
				administration[count].idAdministration = stoi(administrationID);
				administration[count].idCountry = stoi(countryID);
				administration[count].name = name;
				administration[count].currentValue = stoi(currentValue);

				count++;
			}
			else
			{
				cout << endl << "A reading exception occured whilst reading an administration with id " << administrationID << endl;
				cout << "Please double check that the fields are in their correct types and are of compatible values, this administration will be disregarded." << endl << endl;
			}

		}
		catch (exception e) {
			cout << endl << "A casting exception occured whilst reading an administration with id " << administrationID << endl;
			cout << "Please double check that the fields are in their correct types, this administration will be disregarded." << endl << endl;
		}

	}

	adminFile.close();

	return count;
}

string getAdministrationFormat(Administration administration)
{
	stringstream format;
	format << administration.idAdministration << "," << administration.idCountry << "," << administration.name << "," << administration.currentValue;

	return format.str();
}

void writeAdministrationsToDisk(Administration administration[], int TA_SIZE)
{
	string currentLine;

	ofstream adminFile("administrations.csv");

	if (adminFile.is_open()) {
		for(int i = 0; i < TA_SIZE; i++)
			adminFile << getAdministrationFormat(administration[i]) << endl;
	}

	adminFile.close();
}

void reloadAdministrations(Administration administration[], int TA_SIZE)
{
	remove("administrations.csv");
	writeAdministrationsToDisk(administration, TA_SIZE);
}

void displayEvolution(int administrationID, Assessment* T, int size, int startYear, int endYear)
{
	for (int i = 0; i < size; i++)
	{
		if ((T + i)->idAdministration == administrationID)
		{
			if ((T + i)->year >= startYear && (T + i)->year <= endYear)
				displayAssessment(*(T + i));
		}
	}
}