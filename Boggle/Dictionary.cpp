#include "Dictionary.h"

unsigned int HashFunc(const string& word)
{
	unsigned int len = word.length(), first = 0, last = 0;
	char a = word[0], b = word[1], c = word[2];
	char x = word[len - 3], y = word[len - 2], z = word[len - 1];

	first = a+b+c;
	last = x+y+z;

	return (first*last*len)%1193;
}

Dictionary::Dictionary(unsigned int numBucks) : Dict(numBucks, HashFunc)
{
	ifstream fin("engldict.txt", ios_base::in);
	if(fin.is_open())
	{
		string temp;
		while(true)
		{
			fin >> temp;
			if(fin.eof())
				break;
			else if(temp.length() < 3 || temp.length() > 16)
				continue;

			bool noPunc = true;
			for(unsigned int x = 0; x < temp.length(); x ++)
			{
				if(temp[x] == '\'')
				{
					noPunc = false;
					break;
				}
			}

			if(noPunc)
				Dict.insert(temp);
		}

		fin.close();
	}
	Dict.printSomeStuff();
}

bool Dictionary::Valid(const string word)
{
	if(Dict.find(word) != -1)
		return true;
	return false;
}

SLList<string>& Dictionary::operator[] (const unsigned int index)
{
	return Dict[index];
}
