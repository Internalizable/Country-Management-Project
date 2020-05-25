#include <iostream>
using namespace std;

#ifndef DATATYPES_H
#define DATATYPES_H

const int LOGIN_MAX_ROWS = 50, LOGIN_MAX_COLUMNS = 2,
	TC_MAX_SIZE = 250, TA_MAX_SIZE = 1000, TS_MAX_SIZE = 1000;

struct Country
{
	int idCountry;
	string name;
};

struct Administration
{
	int idAdministration;
	int idCountry;
	string name;
	int currentValue;
};

struct Assessment
{
	int idAssessment;
	int idAdministration;
	int value;
	int year;
	int month;
	char evaluator[100];
};
#endif