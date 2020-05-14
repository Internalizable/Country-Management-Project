#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DataTypes.h"
using namespace std;

bool doesAdministrationExist(int administrationID, Administration* T, int a, int b);

bool doesAssessmentExist(int assessmentID, Assessment* T, int size)
{
	for (int i = 0; i < size; i++)
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

void partitionAssessment(Assessment T[], int first, int last, int& pivindex)
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

void sortAssessmentAscending(Assessment T[], int first, int last)
{
	int pivindex;

	if (first < last) {
		partitionAssessment(T, first, last, pivindex);
		sortAssessmentAscending(T, first, pivindex - 1);
		sortAssessmentAscending(T, pivindex + 1, last);
	}

}

void insertAssessment(Assessment assessment, Assessment T[], Administration A[], int& assessmentSize, int administrationSize)
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

int readAssessmentFromDisk(Assessment assessment[])
{
	ifstream assessments;
	string line;

	assessments.open("assessments.txt");

	int count = 0;

	if (!assessments.is_open())
	{
		cout << "File failed to open!" << endl;
		return 0;
	}

	string assessmentID, administrationID, value, year, month, evaluator;

	while (getline(assessments, line))
	{
		stringstream ss(line);

		getline(ss, assessmentID, '\t');
		getline(ss, administrationID, '\t');
		getline(ss, value, '\t');
		getline(ss, year, '\t');
		getline(ss, month, '\t');
		getline(ss, evaluator, '\t');

		assessment[count].idAssessment = stoi(assessmentID);
		assessment[count].idAdministration = stoi(administrationID);
		assessment[count].value = stoi(value);
		assessment[count].year = stoi(year);
		assessment[count].month = stoi(month);

		for (int i = 0; i < evaluator.length(); i++)
		{
			assessment[count].evaluator[i] = evaluator[i];
		}

		count++;
	}

	assessments.close();

	return count;
}

string getAssessmentFormat(Assessment assessment)
{
	stringstream format;
	format << assessment.idAssessment << "\t" << assessment.idAdministration << "\t" << assessment.value << "\t" << assessment.year << "\t" << assessment.month << "\t" << assessment.evaluator;

	return format.str();
}

void writeAssessmentToDisk(Assessment assessment[], int TS_SIZE)
{
	string currentLine;

	ofstream assFile("assessments.txt");

	if (assFile.is_open()) {
		for (int i = 0; i < TS_SIZE; i++)
			assFile << getAssessmentFormat(assessment[i]) << endl;
	}

	assFile.close();
}

void reloadAssessments(Assessment assessment[], int TS_SIZE)
{
	remove("assessments.txt");
	writeAssessmentToDisk(assessment, TS_SIZE);
}

void fillAssessmentArray(Assessment* T, int TS_SIZE, Administration* A, int TA_SIZE)
{
	for (int i = 0; i < TS_SIZE; i++)
		* (T + i) = createAssessment(T, TS_SIZE, A, TA_SIZE);
}