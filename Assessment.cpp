#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DataTypes.h"
using namespace std;

const string ASSESSMENT_PATH = "data\\assessments.csv";


bool doesAdministrationExist(int administrationID, Administration* T, int a, int b);

bool doesAssessmentExist(int assessmentID, Assessment* T, int TS_SIZE)
{
	for (int i = 0; i < TS_SIZE; i++)
		if ((T + i)->idAssessment == assessmentID)
			return true;

	return false;
}

Assessment createAssessment(Assessment *T, int TS_SIZE, Administration *A, int TA_SIZE)
{

	Assessment assessment;

	cout << "Please input the idAssessment for the current Assessment: ";
	cin >> assessment.idAssessment;

	while (doesAssessmentExist(assessment.idAssessment, T, TS_SIZE))
	{
		cout << "\aThe entered idAssessment is not unique, please try again with a unique value: ";
		cin >> assessment.idAssessment;
	}

	while (assessment.idAssessment <= 0)
	{
		cout << "\aThe idAssessment field of the Assessment must be equal or greater than 1, please try again: ";
		cin >> assessment.idAssessment;
	}

	cout << "Please input the idAdministration for the Assessment: ";
	cin >> assessment.idAdministration;

	while (!doesAdministrationExist(assessment.idAdministration, A, 0, TA_SIZE - 1))
	{
		cout << "\aThe idAdministration field of the Assessment is invalid! There's no administration with that ID existent, please try again: ";
		cin >> assessment.idAdministration;
	}

	cout << "Please input the value for the current assessment: ";
	cin >> assessment.value;

	while (assessment.value < 0 || assessment.value > 100)
	{
		cout << "\aThe value field of the Assessment can't be lower than 0 or greater than 100, try again: ";
		cin >> assessment.value;
	}

	cout << "Please input the year for Assessment: ";
	cin >> assessment.year;

	while (assessment.year <= 0)
	{
		cout << "\aThe year field of the Assessment can't be lower or equal to 0, try again: ";
		cin >> assessment.year;
	}

	cout << "Please input the month for Assessment: ";
	cin >> assessment.month;

	while (assessment.month <= 0 || assessment.month > 12)
	{
		cout << "\aThe month field of the Assessment must be between 1 and 12: ";
		cin >> assessment.month;
	}

	cin.ignore();

	cout << "Please input the name of the person for Assessment: ";
	cin.get(assessment.evaluator, 20); //todo constant for people name

	return assessment;
}

void displayAssessment(Assessment T)
{
	cout << endl;
	cout << "Assessment ID: " << T.idAssessment << endl;
	cout << "Assessment Administration ID: " << T.idAdministration << endl;
	cout << "Assessment Value: " << T.value << endl;
	cout << "Assessment Year: " << T.year << endl;
	cout << "Assessment Month: " << T.month << endl;
	cout << "Assessment Evaluator: " << T.evaluator << endl;
	cout << endl;
}

void findAssessment(Assessment* T, int size, int assessmentID)
{
	for (int i = 0; i < size; i++)
	{
		if ((T + i)->idAssessment == assessmentID)
		{
			displayAssessment(*(T + i));
			break;
		}
	}
}

void partitionAssessmentAscending(Assessment T[], int first, int last, int& pivindex)
{
	int pivot = T[first].idAdministration, up = first, down = last;

	do {
		while (T[up].idAdministration <= pivot && up < last)
			up++;
		while (T[down].idAdministration > pivot)
			down--;

		if (up < down)
		{
			Assessment temp = T[up];
			T[up] = T[down];
			T[down] = temp;
		}

	} while (up < down);

	Assessment temp = T[first];
	T[first] = T[down];
	T[down] = temp;

	pivindex = down;
}

void partitionAssessmentDescending(Assessment T[], int first, int last, int& pivindex)
{
	int pivot = T[first].idAdministration, up = first, down = last;

	do {
		while (T[up].idAdministration >= pivot && up < last)
			up++;
		while (T[down].idAdministration < pivot)
			down--;

		if (up < down)
		{
			Assessment temp = T[up];
			T[up] = T[down];
			T[down] = temp;
		}

	} while (up < down);

	Assessment temp = T[first];
	T[first] = T[down];
	T[down] = temp;

	pivindex = down;
}

void sortAssessmentAscending(Assessment T[], int first, int last)
{
	int pivindex;

	if (first < last) {
		partitionAssessmentAscending(T, first, last, pivindex);
		sortAssessmentAscending(T, first, pivindex - 1);
		sortAssessmentAscending(T, pivindex + 1, last);
	}

}

void sortAssessmentDescending(Assessment T[], int first, int last)
{
	int pivindex;

	if (first < last) {
		partitionAssessmentDescending(T, first, last, pivindex);
		sortAssessmentDescending(T, first, pivindex - 1);
		sortAssessmentDescending(T, pivindex + 1, last);
	}

}

void insertAssessment(Assessment assessment, Assessment T[], Administration A[], int& assessmentSize, int administrationSize)
{

	if (assessmentSize != TS_MAX_SIZE)
	{
		int pos = assessmentSize;

		for (int i = assessmentSize - 1; i >= 0; i--)
		{
			if (T[i].idAdministration == assessment.idAdministration)
			{
				pos = i + 1;
				break;
			}
		}

		for (int i = assessmentSize; i > pos; i--)
			T[i] = T[i - 1];

		T[pos] = assessment;

		for (int i = 0; i < administrationSize; i++)
		{
			if (A[i].idAdministration == assessment.idAdministration)
				A[i].currentValue = assessment.value;
		}

		assessmentSize++;
	}
	else
		cout << endl << "ERROR: Unable to add more entries to the assessment array, please consider deleting assessments before trying to add/create new ones!" << endl;

}

void deleteAssessment(Assessment T[], int &assessmentSize, int idAssessment) {
	int pos = -1;

	for (int i = 0; i < assessmentSize; i++)
	{
		if (T[i].idAssessment == idAssessment)
		{
			pos = i;
			break;
		}	
	}

	if (pos != -1)
	{
		for (int i = pos; i < assessmentSize - 1; i++)
		{
			T[i] = T[i + 1];
		}
	}

	assessmentSize--;
}

int readAssessmentFromDisk(Assessment assessment[], Administration TA[], int TA_SIZE)
{
	ifstream assessments;
	string line, assessmentID, administrationID, value, year, month, evaluatorString;;
	int count = 0;

	Assessment temp;

	assessments.open(ASSESSMENT_PATH.c_str());

	if (!assessments.is_open())
	{
		cout << endl << "\aThe assessments file has not been found! Generating a new one..." << endl << endl;
		ofstream generateFile(ASSESSMENT_PATH.c_str());

		if (generateFile.is_open())
			generateFile.close();

		return 0;
	}

	while (getline(assessments, line))
	{
		stringstream ss(line);

		getline(ss, assessmentID, ',');
		getline(ss, administrationID, ',');
		getline(ss, value, ',');
		getline(ss, year, ',');
		getline(ss, month, ',');
		getline(ss, evaluatorString, ',');

		try {

			if (doesAdministrationExist(stoi(administrationID), TA, 0, TA_SIZE - 1))
			{

				if (stoi(value) >= 0 && stoi(value) <= 100)
				{

					if (stoi(year) >= 0 && stoi(month) >= 1 && stoi(month) <= 12)
					{

						if (!doesAssessmentExist(stoi(assessmentID), assessment, count))
						{
							temp.idAssessment = stoi(assessmentID);
							temp.idAdministration = stoi(administrationID);
							temp.value = stoi(value);
							temp.year = stoi(year);
							temp.month = stoi(month);

							for (int i = 0; i <= evaluatorString.length(); i++)
							{
								temp.evaluator[i] = evaluatorString[i];
							}

							insertAssessment(temp, assessment, TA, count, TA_SIZE);
						}
						else
						{
							cout << endl << "A reading exception occured whilst reading an assessment with id " << assessmentID << endl;
							cout << "The assessmentID value mapped with this assessment already exists once! This assessment will be discarded." << endl << endl;
						}
					}
					else
					{
						cout << endl << "A reading exception occured whilst reading an assessment with id " << assessmentID << endl;
						cout << "The year/month value mapped with this assessment is invalid! This assessment will be discarded." << endl << endl;
					}

				}
				else
				{
					cout << endl << "A reading exception occured whilst reading an assessment with id " << assessmentID << endl;
					cout << "The value mapped with this assessment is invalid, it must be between 0 and 100! This assessment will be discarded." << endl << endl;
				}
					

			}
			else
			{
				cout << endl << "A reading exception occured whilst reading an assessment with id " << assessmentID << endl;
				cout << "The administration ID mapped with this assessment is invalid! This assessment will be discarded." << endl << endl;
			}

		} catch (exception e)
		{
			cout << endl << "A casting exception occured whilst reading an assessment with id " << assessmentID << endl;
			cout << "Please double check that the fields are in their correct types, this assessment will be disregarded." << endl << endl;
		}

	}

	assessments.close();

	return count;
}

string getAssessmentFormat(Assessment assessment)
{
	stringstream format;
	format << assessment.idAssessment << "," << assessment.idAdministration << "," << assessment.value << "," << assessment.year << "," << assessment.month << "," << assessment.evaluator;

	return format.str();
}

void writeAssessmentToDisk(Assessment assessment[], int TS_SIZE)
{
	string currentLine;

	ofstream assFile(ASSESSMENT_PATH.c_str());

	if (assFile.is_open()) {
		for (int i = 0; i < TS_SIZE; i++)
			assFile << getAssessmentFormat(assessment[i]) << endl;
	}

	assFile.close();
}

void reloadAssessments(Assessment assessment[], int TS_SIZE)
{
	remove(ASSESSMENT_PATH.c_str());
	writeAssessmentToDisk(assessment, TS_SIZE);
}

void fillAssessmentArray(Assessment* T, int TS_SIZE, Administration* A, int TA_SIZE)
{
	for (int i = 0; i < TS_SIZE; i++)
		* (T + i) = createAssessment(T, TS_SIZE, A, TA_SIZE);
}