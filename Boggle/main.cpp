#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Game.h"

using namespace std;

class DTSTimer
{
	unsigned int startTime;
public:
	DTSTimer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while(clock() - st < milli){}
	}

};

int main (int argc, char ** argv)
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	// LEAK DETECTION
	////////////////////////////////////////////////////////////////////////////////////////////////
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
	//	_CrtSetBreakAlloc();
	DTSTimer bob;
	string userInput;
	srand((unsigned int) time(0));
	bool mode = true, play = true;

	while (play)
	{
		while (true)
		{
			system("cls");
			short temp = 0;
			cout << "BOGGLE!!\n\n\n";
			Beep(750, 100);
			Beep(1200, 150);
			Beep(1500, 200);
			//ask for defualt grid or random grid later
			cout << "Choose a mode: \n";
			cout << "1) Default Grid\n2) Shuffled Grid\n"; 
			if(cin >> temp && (temp > 0 && temp < 3))
			{
				cin.ignore(INT_MAX, '\n');
				if(temp == 2)
					mode = false;
				else
					mode = true;
				break;
			}

			cin.ignore(INT_MAX, '\n');
			cin.clear();
		}

		Game bog(mode);
		bob.reset();
		while(bob.getElapsedTime() < 60000)
		{
			char ch;
			// 1 - get user input
			if(_kbhit())
			{
				ch = _getch();

				if(-32 == ch)
					_getch();
				// did the user press a-z?
				else if(isalpha(ch))
					userInput += tolower(ch);
				//backspace needs to be implimented
				else if(ch == '\b' && userInput.size() != 0)
					userInput.pop_back();


				// 2 - act on it
				if(ch == '\r')
				{
					if(userInput.size() >= 3)
						if(bog.ValidWord(userInput))
							Beep(1500, 100);
						else
							Beep(750, 100);
					else
						Beep(750, 100);
					userInput.clear();
				}
				else if(ch == 27) //check if esc key is pressed
					break;
			}
			// 3 - draw the screen
			system("cls");
			bog.Display();
			cout << 60 - bob.getElapsedTime()/1000;
			cout << '\n' << userInput << '\n';
		}

		//highscore display + replay option
		Beep(1500, 100);
		Beep(1200, 150);
		Beep(750, 200);
		bob.delay(1000);
		//bog.FinishWords(); Took too long to find rest of words :(
		bog.HighScore();
		while (true)
		{
			system("cls");
			char temp = ' ';
			cout << "Would you like to play again (Y/N)? _\b";
			if(cin >> temp && (toupper(temp) == 'Y' || toupper(temp) == 'N'))
			{
				cin.ignore(INT_MAX, '\n');
				if(toupper(temp) == 'N')
					play = false;
				break;
			}

			cin.ignore(INT_MAX, '\n');
			cin.clear();
		}

	}
	//bonus: display all possible words of grid (already know algorithm, just add if have time)

	return 0;
}


