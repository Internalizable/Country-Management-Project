#include <iostream>
using namespace std;

#ifndef DATATYPES_H
#define DATATYPES_H

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
