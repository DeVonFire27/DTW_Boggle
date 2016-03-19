#pragma once
#include "Dictionary.h"
#include "DynArray.h"
#include <ctime>
#include <iostream>
#include <string>
#include "Graph.h"
#include "BST.h"
using namespace std;

class Game
{

public:
	struct Score
	{
		unsigned int score;
		char name[4];

		bool operator<(const Score& rghtSide) const
		{
			return (this->score > rghtSide.score);
		}

		bool operator>=(const Score& rghtSide) const
		{
			return (this->score <= rghtSide.score);
		}

		friend fstream& operator<<(fstream& out, const Score& right)
		{
			out << right.name << '\t' << right.score;
			return out;
		}
		friend ostream& operator<<(ostream& out, const Score& right)
		{
			out << right.name << '\t' << right.score;
			return out;
		}

		Score() {};
		void Set(const char* init, const unsigned int points)
		{
			this->score = points;
			strcpy_s(this->name, 4, init);
		}
	};

private:
	Dictionary Dict;
	Graph<char> grid;
	BST<string> wordUsed; //change to binary search tree and make sure it sorts words
	unsigned int points; //make score factorial of word length

public:
	Game(bool mode);
	~Game(void);
	bool ValidWord(const string word);
	bool MakeWordHelper(const string word, Graph<char>::Vertex startIndex, unsigned int letterIndex, DynArray<unsigned int>& usedIndex);
	void Display();
	void FinishWords();
	unsigned int factorialPoints(unsigned int multi);
	void HighScore();

};

