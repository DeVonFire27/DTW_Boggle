#include "Game.h"

Game::Game(bool mode) : Dict(1193)
{
	//arlwitosenstwpkj
	if(mode)
	{
		char* die = "arlwitosenstwpkj";
		for(int x = 0; x < 16; x++)
			grid.addVertex(die[x]);
	}
	else
	{
		DynArray<char> die;
		char* vowels = "aeiouy";
		for(int x = 0; x < 16; x++)
		{
			if(x < 4)
				die.append(vowels[rand()%6]);
			else
				die.append(rand()%('z' - 'a') + 'a');

			unsigned int index1 = rand()%die.size(), index2 = rand()%die.size();
			char temp = die[index1];
			die[index1] = die[index2];
			die[index2] = temp;	
		}
		for(int x = 0; x < 16; x++)
			grid.addVertex(die[x]);
	}
	//-5 -> +5

	for(int x = 0; x < 16; x++)
	{
		for(int y = -5; y <= 5; y++)
		{
			if(y == 2 || y == -2)
				continue;
			int adj = x + y;
			if(adj >= 0 && adj < 16)
			{
				if((x%4 == 0) &&  (y != 3 && y != -1))
					grid[x].addEdge(adj);
				else if(((x-3)%4 == 0) && (y != -3 && y != 1))
					grid[x].addEdge(adj);
				else if((x%4 != 0) && ((x-3)%4 != 0))
					grid[x].addEdge(adj);
			}
		}
	}

	points = 0;

}


Game::~Game(void)
{
}

bool Game::ValidWord(const string word)
{
	if(Dict.Valid(word))
	{
		//if to see if done before
		if(wordUsed.find(word))
			return false;
		//need check to prevent looking at letters on grid
		//already looked at
		for(int x = 0; x < 16; x++)
		{
			DynArray<unsigned int> usedIndex;
			usedIndex.append(x);
			if(MakeWordHelper(word, grid[x], 0, usedIndex))
			{
				points+= factorialPoints(word.size()); //make score factorial of word length
				wordUsed.insert(word);
				return true;
			}
		}

	}

	return false;
}

unsigned int Game::factorialPoints(unsigned int multi)
{
	if(multi > 1)
		multi *= (factorialPoints(multi-1));
	return multi;
}

bool Game::MakeWordHelper(const string word, Graph<char>::Vertex startIndex, unsigned int letterIndex, DynArray<unsigned int>& usedIndex)
{

	if(word[letterIndex] == startIndex.element)
	{
		if(word.length() == letterIndex+1)
			return true;

		SLLIter<Graph<char>::Edge> x(startIndex.edges);
		bool good;
		for(x.begin(); !x.end(); ++x)
		{
			good = true;
			for(unsigned int y = 0; y < usedIndex.size(); y++)
				if(usedIndex[y] == x.current().toVertex)
					good = false;
			if(good)
			{
				usedIndex.append(x.current().toVertex);
				if(MakeWordHelper(word, grid[x.current().toVertex], letterIndex+1, usedIndex))
					return true;
				else
				{
					DynArray<unsigned int> temp;
					temp.reserve(usedIndex.size()-1);
					for(unsigned int x = 0; x < usedIndex.size() - 1; x++)
						temp.append(usedIndex[x]);
					usedIndex.clear();
					usedIndex = temp;
				} 
			}
		}
	}
	return false;
}

void Game::HighScore()
{
	Score newScore;
	BST<Score> theScore;
	char name[4];
	unsigned int pts;
	ifstream fin("HighScores.bin", ios_base::in | ios_base::binary);
	system("cls");
	cout << "GAME OVER\n\nFinal Score: " << points << '\n';
	cout << "Enter Intials: ___\b\b\b";
	cin.get(name, 4, '\n');
	system("cls");
	newScore.Set(name, points);
	theScore.insert(newScore);
	cout << "TOP 10 HIGHSCORES!!!\n\n======================================\n";

	for(int x = 0; x < 10; x++)
	{
		if (fin.is_open())
		{
			fin.getline(name, 4, '\t');
			if(fin.eof())
				break;
			fin >> pts;
			fin.ignore(INT_MAX, '\n');
			newScore.Set(name, pts);
			theScore.insert(newScore); 
		}
		else
			break;
	}

	theScore.printInOrderTxt();
	system("pause");

}

void Game::FinishWords()
{
	BST<string> CompWords;
	unsigned int x = 0, calls = 0;
	for(; x < 1193 && calls <= 20; x++)
	{
		SLLIter<string> iter(Dict[x]);
		for(iter.begin(); !iter.end(); ++iter)
		{
			for(int y = 0; y < 16; y++)
			{
				DynArray<unsigned int> usedIndex;
				usedIndex.append(y);
				if(MakeWordHelper(iter.current(), grid[y], 0, usedIndex))
				{
					CompWords.insert(iter.current());
					calls++;
				}
			}
		}
	}
	cout << "============================================\n";
	cout << "20 other possible grid words:\n";
	CompWords.printInOrder();
	system("pause");

}

void Game::Display()
{
	for(int x = 1; x <= 16; x++)
	{
		cout << grid[x-1].element << ' ';
		if(x%4 == 0)
			cout << '\n';
	}
	cout << "Score: " << points << " -----------------------------------\n";
	wordUsed.printInOrder();
	cout << "\n---------------------------------------------------------\n";
}
