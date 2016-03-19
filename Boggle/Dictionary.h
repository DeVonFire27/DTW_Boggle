#pragma once
#pragma once

#include "HTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Dictionary
{
	HTable<string> Dict;

public:
	Dictionary(unsigned int numBucks);
	bool Valid(const string word);
	SLList<string>& operator[] (const unsigned int index);
};
