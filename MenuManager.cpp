#include <iostream>
#include "DataTypes.h"

using namespace std;

void openCreationMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE);
void openMainMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE);

bool doesCountryExist(int countryID, Country* T, int size);
Country createCountry(Country* T, int TC_SIZE);
void findCountry(Country* T, int size, int countryID);
void displayAdministrationsByValue(int countryID, Administration* T, int size, int value = 100);
void displayCountry(Country c);
void sortCountryAscending(Country* T, int size);
void insertCountry(Country country, Country T[], int& countrySize);
void deleteCountry(Country T[], int& countrySize, int idCountry);
int readCountryFromDisk(Country country[]);
void reloadCountries(Country country[], int TC_SIZE);

bool doesAdministrationExist(int administrationID, Administration* T, int a, int b);
Administration createAdministration(Administration* T, Country* C, int TA_SIZE, int TC_SIZE);
void findAdministration(Administration* T, int size, int administrationID);
void displayAdministration(Administration administration);
void sortAdministrationAscending(Administration T[], int first, int last);
void displayEvolution(int administrationID, Assessment* T, int size, int startYear, int endYear);
void insertAdministration(Administration administration, Administration TA[], int& TA_SIZE);
void deleteAdministration(Administration T[], int& administrationSize, int idAdmin);
int readAdministrationFromDisk(Administration administration[], Country TC[], int TC_SIZE);
void reloadAdministrations(Administration administration[], int TA_SIZE);

bool doesAssessmentExist(int assessmentID, Assessment* T, int size);
Assessment createAssessment(Assessment* T, int TS_SIZE, Administration* A, int TA_SIZE);
void findAssessment(Assessment* T, int size, int assessmentID);
void sortAssessmentAscending(Assessment T[], int first, int last);
void insertAssessment(Assessment assessment, Assessment T[], Administration A[], int& assessmentSize, int administrationSize);
void deleteAssessment(Assessment T[], int& assessmentSize, int idAssessment);
void displayAssessment(Assessment T);
int readAssessmentFromDisk(Assessment assessment[], Administration TA[], int TA_SIZE);
void reloadAssessments(Assessment assessment[], int TS_SIZE);


enum MAIN_MENU_ITEMS 
{
	SHOW, CREATE, DELETE, SEARCH, MANAGE, MANUAL_SAVE, EXIT
};

enum SHOW_MENU_ITEMS
{
	COUNTRY_SHOW, ADMINISTRATION_SHOW, ASSESSMENT_SHOW, EXIT_SHOW
};

enum CREATE_MENU_ITEMS
{
	COUNTRY_CREATION, ADMINISTRATION_CREATION, ASSESSMENT_CREATION, EXIT_CREATION
};

enum DELETE_MENU_ITEMS
{
	COUNTRY_DELETION, ADMINISTRATION_DELETION, ASSESSMENT_DELETION, EXIT_DELETION
};

enum SEARCH_MENU_ITEMS
{
	COUNTRY_SEARCH, ADMINISTRATION_SEARCH, ASSESSMENT_SEARCH, EXIT_SEARCH
};

enum MANAGEMENT_MENU_ITEMS
{
	COUNTRY_SORT, ADMINISTRATION_SORT, ASSESSMENT_SORT, SHOW_LOWER_VALUE, EVOLUTION_OF_INNOVATION,EXIT_MANAGEMENT
};

void openShowMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t      Public Innovations Management - Show Submenu" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Show available countries" << endl;
		cout << "1- Show available administrations" << endl;
		cout << "2- Show available assessments" << endl;
		cout << "3- Exit to main menu mode" << endl << endl;

		cout << "Please input your creation choice: ";
		cin >> choice;

		cout << endl << endl;

	} while (choice < 0 || choice > 3);

	switch (choice)
	{
	case COUNTRY_SHOW:
		for (int i = 0; i < TC_SIZE; i++)
			displayCountry(TC[i]);

		system("pause");
		openShowMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case ADMINISTRATION_SHOW:
		for (int i = 0; i < TA_SIZE; i++)
			displayAdministration(TA[i]);

		system("pause");
		openShowMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case ASSESSMENT_SHOW:
		for (int i = 0; i < TS_SIZE; i++)
			displayAssessment(TS[i]);

		system("pause");

		openShowMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case EXIT_SHOW:
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	
}

void openCreationMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t      Public Innovations Management - Creation Submenu" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Create a new country" << endl;
		cout << "1- Create a new administration" << endl;
		cout << "2- Create a new assessment" << endl;
		cout << "3- Exit to main menu mode" << endl << endl;

		cout << "Please input your creation choice: ";
		cin >> choice;

		cout << endl << endl;
		
	} while (choice < 0 || choice > 3);

	switch (choice)
	{
	case COUNTRY_CREATION:
	{
		Country country = createCountry(TC, TC_SIZE);
		insertCountry(country, TC, TC_SIZE);
		reloadCountries(TC, TC_SIZE);

		openCreationMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case ADMINISTRATION_CREATION:
	{
		
		if (TC_SIZE != 0)
		{
			Administration administration = createAdministration(TA, TC, TA_SIZE, TC_SIZE);
			insertAdministration(administration, TA, TA_SIZE);
			reloadAdministrations(TA, TA_SIZE);
		}
		else
		{
			cout << endl << "Error! Please create a country before creating an administration." << endl << endl;
		}
		

		openCreationMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
	case ASSESSMENT_CREATION:
	{
		if (TA_SIZE != 0)
		{
			Assessment assessment = createAssessment(TS, TS_SIZE, TA, TA_SIZE);
			insertAssessment(assessment, TS, TA, TS_SIZE, TA_SIZE);
			reloadAssessments(TS, TS_SIZE);
		}
		else
		{
			cout << endl << "Error! Please create an administration before creating an assessment." << endl << endl;
		}

		openCreationMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case EXIT_CREATION:
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	
}

void openDeletionMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t      Public Innovations Management - Deletion Submenu" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Delete a country" << endl;
		cout << "1- Delete an administration" << endl;
		cout << "2- Delete an assessment" << endl;
		cout << "3- Exit to main menu mode" << endl << endl;

		cout << "Please input your deletion choice: ";
		cin >> choice;

		cout << endl << endl;

	} while (choice < 0 || choice > 3);

	switch (choice)
	{
	case COUNTRY_DELETION:
	{

		if (TC_SIZE != 0)
		{
			int countryID;

			cout << "Please input the country's ID: ";
			cin >> countryID;

			while (!doesCountryExist(countryID, TC, TC_SIZE))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> countryID;
			}

			deleteCountry(TC, TC_SIZE, countryID);
			reloadCountries(TC, TC_SIZE);
		}
		else cout << "\aError! Please create at least a country before trying to delete one." << endl;

		openDeletionMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case ADMINISTRATION_DELETION:
	{

		if (TA_SIZE != 0)
		{
			int adminID;

			cout << "Please input the administration's ID: ";
			cin >> adminID;

			while (!doesAdministrationExist(adminID, TA, 0, TA_SIZE - 1))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> adminID;
			}

			deleteAdministration(TA, TA_SIZE, adminID);
			reloadAdministrations(TA, TA_SIZE);
		} 
		else cout << "\aError! Please create at least an administration before trying to delete one." << endl;

		openDeletionMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
	case ASSESSMENT_DELETION:
	{

		if (TS_SIZE != 0)
		{
			int assessmentID;

			cout << "Please input the assessment's ID: ";
			cin >> assessmentID;

			while (!doesAssessmentExist(assessmentID, TS, TS_SIZE))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> assessmentID;
			}

			deleteAssessment(TS, TS_SIZE, assessmentID);
			reloadAssessments(TS, TS_SIZE);
		}
		else cout << "\aError! Please create at least an assessment before trying to delete one." << endl;

		openDeletionMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case EXIT_DELETION:
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
}

void openSearchMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t      Public Innovations Management - Search Submenu" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Search for a country" << endl;
		cout << "1- Search for an administration" << endl;
		cout << "2- Search for an assessment" << endl;
		cout << "3- Exit to main menu mode" << endl << endl;

		cout << "Please input your search choice: ";
		cin >> choice;

		cout << endl << endl;

	} while (choice < 0 || choice > 3);

	switch (choice)
	{
	case COUNTRY_SEARCH:
	{
		if (TC_SIZE != 0)
		{
			int countryID;

			cout << "Please input the country's ID: ";
			cin >> countryID;

			while (!doesCountryExist(countryID, TC, TC_SIZE))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> countryID;
			}

			findCountry(TC, TC_SIZE, countryID);

		} else
			cout << "\aError! Please create a country before trying to search for one." << endl;

		openSearchMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case ADMINISTRATION_SEARCH:
	{
		if (TA_SIZE != 0)
		{
			int adminID;

			cout << "Please input the administration's ID: ";
			cin >> adminID;

			while (!doesAdministrationExist(adminID, TA, 0, TA_SIZE - 1))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> adminID;
			}

			findAdministration(TA, TA_SIZE, adminID);

		}
		else
			cout << "\aError! Please create an administration before trying to search for one." << endl;

		openSearchMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case ASSESSMENT_SEARCH:
	{
		if (TS_SIZE != 0)
		{
			int assessmentID;

			cout << "Please input the assessment's ID: ";
			cin >> assessmentID;

			while (!doesAssessmentExist(assessmentID, TS, TS_SIZE))
			{
				cout << "\aThe ID you just specified is invalid, please try again: ";
				cin >> assessmentID;
			}

			findAssessment(TS, TS_SIZE, assessmentID);

		}
		else
			cout << "\aError! Please create an assessment before trying to search for one." << endl;

		openSearchMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case EXIT_SEARCH:
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
}

void openManagementMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t      Public Innovations Management - Management Submenu" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Sort countries in ascending mode based on countryID." << endl;
		cout << "1- Sort administrations in ascending mode based on administrationID" << endl;
		cout << "2- Sort assessments in ascending mode based on administrationID" << endl;
		cout << "3- Display the names of the administrations of a given country having a current value lower than a certain value" << endl;
		cout << "4- Display the evolution of the innovation for a given administration between two specific years." << endl;
		cout << "5- Exit the program" << endl << endl;

		cout << "Please input your management choice: ";
		cin >> choice;

		cout << endl << endl;
	} while (choice < 0 || choice > 5);

	switch (choice)
	{
	case COUNTRY_SORT:
		sortCountryAscending(TC, TC_SIZE);

		for (int i = 0; i < TC_SIZE; i++)
			displayCountry(TC[i]);

		system("pause");
		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);

		break;
	case ADMINISTRATION_SORT:
		sortAdministrationAscending(TA, 0, TA_SIZE - 1);

		for (int i = 0; i < TA_SIZE; i++)
			displayAdministration(TA[i]);

		system("pause");
		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);

		break;
	case ASSESSMENT_SORT:
		sortAssessmentAscending(TS, 0, TS_SIZE - 1);

		for (int i = 0; i < TS_SIZE; i++)
			displayAssessment(TS[i]);

		system("pause");
		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);

		break;
	case SHOW_LOWER_VALUE:
	{
		int value, countryID;

		cout << "Please input the country id: ";

		cin >> countryID;
		
		while (!doesCountryExist(countryID, TC, TC_SIZE))
		{
			cout << "There's no country with that countryID, please try again: ";
			cin >> countryID;
		}

		cout << "Please input a value: ";

		cin >> value;

		while (value < 0 || value > 100)
		{
			cout << "Value must be between 0 and 100, please try again: ";
			cin >> value;
		}

		displayAdministrationsByValue(countryID, TA, TA_SIZE, value);

		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}

	case EVOLUTION_OF_INNOVATION:

		int startYear, endYear, administrationID;

		cout << "Please input the administrationID: ";
		cin >> administrationID;

		while (!doesAdministrationExist(administrationID, TA, 0, TA_SIZE - 1))
		{
			cout << "The following administration doesn't exist, please try again: ";
			cin >> administrationID;
		}

		cout << "Please input a start year followed by an end year: ";
		cin >> startYear >> endYear;

		while (startYear < 0 || endYear < 0 || startYear > endYear)
		{
			cout << "Incorrect arguments! Please try again, input a start year followed by an end year: ";
			cin >> startYear >> endYear;
		}

		displayEvolution(administrationID, TS, TS_SIZE, startYear, endYear);

		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case EXIT_MANAGEMENT:
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
}

void openMainMenu(Country TC[], Administration TA[], Assessment TS[], int TC_SIZE, int TA_SIZE, int TS_SIZE)
{
	int choice;

	do {
		cout << "\t***********************************************************" << endl;
		cout << "\a\t  Welcome to the public innovations management main menu!" << endl;
		cout << "\t***********************************************************" << endl << endl;

		cout << "0- Enter show mode" << endl;
		cout << "1- Enter creation mode" << endl;
		cout << "2- Enter deletion mode" << endl;
		cout << "3- Enter search mode" << endl;
		cout << "4- Enter management mode" << endl;
		cout << "5- Manually save current information and files" << endl;
		cout << "6- Exit the program" << endl << endl;

		cout << "Please input your submenu choice: ";
		cin >> choice;

		cout << endl << endl;
	} while (choice < 0 || choice > 6);

	switch (choice)
	{
	case SHOW:
		openShowMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case CREATE:
		openCreationMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case DELETE:
		openDeletionMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case SEARCH:
		openSearchMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case MANAGE:
		openManagementMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	case MANUAL_SAVE:
		reloadCountries(TC, TC_SIZE);
		reloadAdministrations(TA, TA_SIZE);
		reloadAssessments(TS, TS_SIZE);
		openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
		break;
	}
}

void getStartupConfigurations()
{
	Country TC[250];
	Administration TA[1000];
	Assessment TS[1000];

	int TC_SIZE = readCountryFromDisk(TC),
		TA_SIZE = readAdministrationFromDisk(TA, TC, TC_SIZE),
		TS_SIZE = readAssessmentFromDisk(TS, TA, TA_SIZE);

	openMainMenu(TC, TA, TS, TC_SIZE, TA_SIZE, TS_SIZE);
}