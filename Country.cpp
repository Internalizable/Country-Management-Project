#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DataTypes.h"
using namespace std;

const string COUNTRIES_PATH = "data\\countries.csv";

bool doesCountryExist(int countryID, Country* T, int size)
{
	for (int i = 0; i < size; i++)
		if ((T + i)->idCountry == countryID)
			return true;

	return false;
}

Country createCountry(Country *T, int TC_SIZE) {

	Country country;

	cout << "Please input the country's ID: ";

	cin >> country.idCountry;

	while (doesCountryExist(country.idCountry, T, TC_SIZE))
	{
		cout << "\aThe entered idCountry is not unique, please try again with a unique value: ";
		cin >> country.idCountry;
	}

	while (country.idCountry <= 0)
	{
		cout << "\aThe idCountry field of the Country must be equal or greater than 1, please try again: ";
		cin >> country.idCountry;
	}

	cin.ignore();

	string countryName;

	cout << "Please input the name of the country: ";
	getline(cin, countryName);

	country.name = countryName;

	return country;
}

void displayCountry(Country c)
{
	cout << endl;
	cout << "Country ID: " << c.idCountry << endl;
	cout << "Country Name: " << c.name << endl;
	cout << endl;
}

void findCountry(Country* T, int size, int countryID)
{
	for (int i = 0; i < size; i++)
	{
		if ((T + i)->idCountry == countryID)
		{
			displayCountry(*(T + i));
			break;
		}
	}
}

void sortCountryAscending(Country* T, int size)
{
	int posmin;

	for (int i = 0; i < size - 1; i++)
	{
		posmin = i;

		for (int j = i + 1; j < size; j++)
				if ((T + j)->idCountry < (T + posmin)->idCountry)
					posmin = j;

		Country temp = *(T + posmin);
		*(T + posmin) = *(T + i);
		*(T + i) = temp;
	}
}

void sortCountryDescending(Country* T, int size)
{
	int posmin;

	for (int i = 0; i < size - 1; i++)
	{
		posmin = i;

		for (int j = i + 1; j < size; j++)
			if ((T + j)->idCountry > (T + posmin)->idCountry)
				posmin = j;

		Country temp = *(T + posmin);
		*(T + posmin) = *(T + i);
		*(T + i) = temp;
	}
}

void insertCountry(Country country, Country T[], int& countrySize)
{
	if (countrySize != TC_MAX_SIZE)
	{
		T[countrySize] = country;
		countrySize++;
	}
	else
		cout << endl << "ERROR: Unable to add more entries to the country array, please consider deleting countries before trying to add/create new ones!" << endl;
}

void deleteCountry(Country T[], int &countrySize, int idCountry) {
	int pos = -1;

	for (int i = 0; i < countrySize; i++)
	{
		if (T[i].idCountry == idCountry)
		{
			pos = i;
			break;
		}
	}

	if (pos != -1)
	{
		for (int i = pos; i < countrySize - 1; i++)
		{
			T[i] = T[i + 1];
		}
	}

	countrySize--;
}

void displayAdministrationsByValue(int countryID, Administration* T, int size, int value = 100)
{
	cout << endl;
	cout << "The Country " << countryID << " administrations with values under " << value << " are: " << endl;

	for (int i = 0; i < size; i++)
	{
		if ((T + i)->idCountry == countryID)
		{
			if ((T + i)->currentValue <= value)
				cout << (T + i)->name << endl;
		}

	}

	cout << endl;
}

int readCountryFromDisk(Country country[])
{
	ifstream countries;
	string line, countryName, countryID;
	int count = 0;

	Country temp;

	countries.open(COUNTRIES_PATH.c_str());


	if (!countries.is_open())
	{
		cout << endl << "\aThe countries file has not been found! Generating a new one..." << endl << endl;
		ofstream generateFile(COUNTRIES_PATH.c_str());

		if (generateFile.is_open())
			generateFile.close();

		return 0;
	}

	while (getline(countries, line))
	{
		stringstream ss(line);

		getline(ss, countryID, ',');
		getline(ss, countryName, ',');

		try {

			if (!doesCountryExist(stoi(countryID), country, count))
			{
				temp.idCountry = stoi(countryID);
				temp.name = countryName;

				insertCountry(temp, country, count);
			}
			else
			{
				cout << endl << "A conflict exception occured whilst reading a country with id " << countryID << endl;
				cout << "Please double check that the country id is unique and it doesn't conflict with existing IDS." << endl << endl;
			}

		}
		catch (exception e)
		{
			cout << endl << "A casting exception occured whilst reading a country with id " << countryID << endl;
			cout << "Please double check that the fields are in their correct types, this country will be disregarded." << endl << endl;
		}
	}

	countries.close();

	return count;
}

string getCountryFormat(Country country)
{
	stringstream format;
	format << country.idCountry << "," << country.name;

	return format.str();
}

void writeCountriesToDisk(Country country[], int TC_SIZE)
{
	string currentLine;

	ofstream countryFile(COUNTRIES_PATH.c_str());

	if (countryFile.is_open()) {
		for (int i = 0; i < TC_SIZE; i++)
			countryFile << getCountryFormat(country[i]) << endl;
	}

	countryFile.close();
}

void reloadCountries(Country country[], int TC_SIZE)
{
	remove(COUNTRIES_PATH.c_str());
	writeCountriesToDisk(country, TC_SIZE);
}