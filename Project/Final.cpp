/**************************************************************************
*Function Name      :    Final
*Author             :    Joe McCarthy, Tyler Myers, Loren Davies
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:    
*
*BEGIN main
* 	
*END main
**************************************************************************/

#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;


// Structures
struct Phrase;

struct Phrase
{
	string Category;					// Date of the game
	string Text;						// Who they played against
}; // END PHRASE

// Global Constants
const int MAX_SIZE = (30);
const int MAX_PLAYERS = 4;

//Prototypes
int main_menu();
int turn_menu();
void heading(Player[], int);
bool next_round();
int insert_file(string, Phrase[], int);
int spin_wheel();
string create_blank(string);
int guess_letter(string, string&, string);
int element_delete(Phrase[], int, int);
int search(Phrase[], int);
void main_heading();
string display_phrase(string, string);


int main()
{

	// Local constants
	const string BLANK = " ";

	// Local variables
	Phrase Array[MAX_SIZE];
	Phrase Game_Phrase;
	Player Player_Array[MAX_PLAYERS];
	Player Round_Array[MAX_PLAYERS];
	int Choice = 0;				// The users choice in the main menu
	int Turn_Choice = 0; 		// The users choice in the turn menu
	int Num_Players = 0; 		// The number of players playing the game
	int Phrase_Count = 0; 		// The number of phrases entered into the array
	int Spin_Value = 0;			// The returned value from spinning the wheel
	int Phrase_Index = 0;
	int Letter_Value = 0;
	string File_Name = "";		// The users entered file
	string Temp;
	string Current_Phrase = "";
	string Guessed_Letters;
	string Player_Guess;
	bool Round_Continue = true;	// The player chooses to continue to another round
	bool File_Entered = false;	// Becomes true if the user enters a file
	bool Solved = false;


	//Player players[] = PLAYER_ARRAY_SIZE;
	/*************************** Start main ***************************/

	// Call main heading
	main_heading();

	//Call the main menu
	Choice = main_menu();
	
	// WHILE Choice != QUIT
	while(Choice != 4)
	{
		
		// SWITCH Choice
		switch(Choice)
		{
			
			// They pick start a new game
			case 1:
				
				// IF there is no file entered
				if (!File_Entered)
				{
					// Enter default file and set File_Entered to true
					Phrase_Count = insert_file("default.txt", Array, Phrase_Count);
					File_Entered = true;
				}

				// Call main heading
				main_heading();

				// Get number of players from the user
				cout << setw(40) << "Number of players (1-4): ";
				cin >> Num_Players;

				// Get the players names
				for(int i = 0; i < Num_Players; i++)
				{
					cout << setw(25) << (i+1) << ") Player Name: ";
					cin >> Temp;
					Player_Array[i].Name = Temp;
				}

				// Call main heading
				main_heading();

				// WHILE user chooses to continue to another round
				while (Round_Continue)
				{
					// Get a new random phrase
					Phrase_Index = rand() % Phrase_Count;
					Game_Phrase = Array[Phrase_Index];
					cout << setw(40) << "Category: " << Game_Phrase.Category << endl;

					// Delete the phrase
					Phrase_Count = element_delete(Array, Phrase_Count, Phrase_Index);

					// Make the blank spaces board
					Current_Phrase = create_blank(Game_Phrase.Text);
					guess_letter(Game_Phrase.Text , Current_Phrase , BLANK);

					// WHILE the puzzle is not solved
					while(!Solved)
					{
						
						//  Set the players names for the round array
						for(int i = 0; i < Num_Players; i++)
						{
							Round_Array[i].Name = Player_Array[i].Name;
						}

						//  FOR every player
						for(int i = 0; i < Num_Players; i++)
						{
							// WHILE players turn is up
							while(Round_Array[i].Turn == 1)
							{
								if (Round_Array[i].Turn == 0)
								{
									if((i+1) == Num_Players)
									{
										Round_Array[0].Turn = 1;
									}
									else
									{
										Round_Array[i+1].Turn = 1;
									}
								}

								heading(Round_Array, Num_Players);
								
								cout << display_phrase(Game_Phrase.Text, Player_Guess);

								// Turn menu
								Turn_Choice = turn_menu();
								switch(Turn_Choice)
								{
									// Sping the wheel
									case 1:
										Spin_Value = spin_wheel();
										cout << "Points: " << Spin_Value;

										//IF spin value = Bankrupt
										if (Spin_Value == 1)
										{
											Round_Array[i].Score = 0;
											Round_Array[i].Turn = 0;
											if((i+1) != Num_Players)
											{
												Round_Array[i+1].Turn += 1;
											}
											break;
										}// END IF

										//IF players turn
										if(Spin_Value == (-1))
										{
											Round_Array[i].Turn = -1;
											if((i+1) != Num_Players)
											{
												Round_Array[i+1].Turn += 1;
											}
											break;

										}// END IF
										else
										{
											cout << "\n\n";
											cout << "Input your guess: ";
											cin >> Player_Guess;
											Letter_Value = guess_letter(Game_Phrase.Text , Current_Phrase , Player_Guess);

											if(Letter_Value == 0)
											{
												Round_Array[i].Turn = 0;
												if((i+1) != Num_Players)
												{
													Round_Array[i+1].Turn = 1;
													break;
												}
												else
												{
													i = 0;
													Round_Array[i].Turn += 1;
												}
												
											}// END IF
											else
											{
												Round_Array[i].Score += Spin_Value*Letter_Value;
												Round_Array[i].Turn = 1;
												break;
											}// END IF


										}//END ELSE

									case 2:
										cout << "Enter a vowel for $250: ";
										break;


									case 3:
										cout << Game_Phrase.Category << ": " << endl;
										cout << Current_Phrase << endl;
										cout << "Your answer: ";
										getline(cin, Player_Guess);


										if((Player_Guess) == (Game_Phrase.Text))
										{
											Solved = true;
											Player_Array[i].Score += Round_Array[i].Score;
										}

										break;


								}//END TURN_CHOICE SWITCH

							}// END TURN WHILE
						}//END TURN SYSTEM FOR


					}// END SOLVED WHILE


					Guessed_Letters = "";
					for(int i = 0; i < Num_Players; i++)
					{
						Round_Array[i].Score = 0;
					}
					if (next_round())
					{
						Round_Continue = true;
					}
					else
					{
						Round_Continue = false;
					}
				}// END ROUND_CONTINUE WHILE

				break;
				
			// They pick input a new file
			case 2:
				cout << "Enter a file name: ";
				cin >> File_Name;
				Phrase_Count = insert_file(File_Name, Array, Phrase_Count);
				File_Entered = true;
				break;

			//They pick view rules and odds
			case 3:
				cout << "";
				break;


		}
		Choice = main_menu();
	}// END WHILE

}// END MAIN PROGRAM

// Main menu
int main_menu()
{
	int Choice = 0;
	cout << setw(49) << "1) Start new game" << endl;
	cout << setw(49) << "2) Input new file" << endl;
	cout << setw(45) << "3) View rules" << endl;
	cout << setw(40) << "4) Quit " << endl;
	cout << setw(36) << "--> ";
	cin >> Choice;
	return Choice;
}

//Turn menu
int turn_menu()
{
	int Choice = 0;
	cout << "\n\n\n";
	cout << setw(49) << "1) Spin the wheel" << endl;
	cout << setw(46) << "2) Buy a vowel" << endl;
	cout << setw(51) << "3) Solve the puzzle" << endl;
	cout << setw(36) << "--> ";
	cin >> Choice;
	return Choice;
}

//Heading
void heading(Player Array[], int Num)
{
	switch(Num)
	{
		case 1:
			cout << setw(45) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score <<  endl;
			break;
		case 2:
			cout << setw(45) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(45) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score <<  endl;
			break;
		case 3:
			cout << setw(45) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(45) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score << endl;
			cout << setw(45) << Array[2].Name << "'s ";
			cout << "score: " << Array[2].Score <<  endl;
			
			break;
		case 4:
			cout << setw(45) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(45) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score << endl;
			cout << setw(45) << Array[2].Name << "'s ";
			cout << "score: " << Array[2].Score <<  endl;
			cout << setw(45) << Array[3].Name << "'s ";
			cout << "score: " << Array[3].Score <<  endl;
			break;
		default:
			cout << "Invalid Input";
	}
}

bool next_round()
{
	int Choice = 0;

	while ((Choice != 1) || (Choice != 2))
	cout << "Would you like to play another round? " << endl;
	cout << "1) Yes " << endl;
	cout << "2) No " <<endl;
	cout << "-->  " ;
	cin >> Choice;

	if(Choice == 1)
	{
		return true;
	}

	else if(Choice == 2)
	{
		return false;
	}

	else
	{
		return false;
	}

}

/**************************************************************************
 *Function Name      :    insertFile
 *Author             :    Loren Davies
 *Date               :    11/20/2015
 *Course/Section     :    CSC 263 - 001
 *Program Description:    Reads line from txt file, and adds it to
 * structure. Then call function to add it to array.
 *
 *BEGIN insertFile
 * 	Input file name
 *	Open file
 *	IF there's a problem opening a file
 *		Output error message
 *	ELSE file did open properly
 *		Read first line, but do nothing with it
 *		WHILE it isn't the end of the file
 *			Input Game_Number add to game
 *			Input Date add to game
 *			Input Opponent add to game
 *			Input Home_Away add to game
 *			IF Home_Away doesn't equal A or H
 *				Add Home_Away to Opponent
 *				Input Home_Away add to game
 *			END IF
 *			Input Score add to game
 *			Input Their_Score add to game
 *			Input Result add to game
 *			Parse and add Game_Number to Game
 *		END WHILE
 *END insertFile
 **************************************************************************/
int insert_file(string File_Name, Phrase Array[], int Count)
 {
 	// Local constants


 	// Local variables
	string Current_Line;				// Line being read
	Phrase phrase;
	ifstream fs;						// Input stream


 	/****************************** start insert_file ******************************/

	// Open file
	fs.open(File_Name.c_str());



	// IF there's a problem opening the file
	if(fs.fail())
	{
		// Output error message
		cout << "File DNE" << endl;
	}

	// ELSE file did open properly

		// Read first line, but do nothing with it
		getline(fs, Current_Line);

		// WHILE it isn't the end of the file
		while(!fs.eof())
		{
			if(Count == MAX_SIZE)
			{
				fs.eof();
			}
			// Input Category
			getline(fs, phrase.Category, '-');

			// Get rid of the space at the end
			phrase.Category.erase(phrase.Category.length(),1);

			// Input Phrase Text
			getline(fs, phrase.Text, '\n');

			// Get rid of the space at the start
			phrase.Text.erase(0,1);

			Array[Count] = phrase;

			Count++;
		}


	for(int i = 0; i < Count; i++)
	{
		cout << Array[i].Category << endl;
		cout << Array[i].Text << endl;
		cout << "----------" << endl;
	}

	return Count;
 }
 
 string display_phrase(string Phrase, string Letter)
 {
 	// Local constants
 	
 	// Local variables
 	string Temp = Phrase;
 	char c;
 	
 	/*************************** Start display_phrase ***************************/
 	
 	for(int i = 0; i < Phrase.length(); i++)
 	{
 		c = Phrase[i];
 		
 		if(isspace(c))
		{
			Temp.replace(i, i, " ");
		}
		
 		else if(c == Letter[0])
 		{
 			Temp.replace(i, i, Letter);
		}
		
		else
		{
			Temp.replace(i, i, "_");
		}
	}
 	
 	return Temp;
 }

//User spins the wheel
int spin_wheel()
{
	// Local constants
	const int VALUE1 = 250;
	const int VALUE2 = 500;
	const int VALUE3 = 750;
	const int VALUE4 = 1000;
	const int VALUE5 = 1500;
	const int BANKRUPT = 1;
	const int LOSE_TURN = -1;

	// Local variables
	int num = 1;
	int wheel [MAX_SIZE];

	// Wheel Values
	wheel[0] = VALUE1;
	wheel[1] = VALUE1;
	wheel[5] = BANKRUPT;
	wheel[3] = VALUE1;
	wheel[4] = VALUE1;
	wheel[2] = VALUE2;
	wheel[6] = VALUE5;
	wheel[7] = VALUE2;
	wheel[8] = VALUE2;
	wheel[9] = VALUE2;
	wheel[17] = VALUE3;
	wheel[11] = VALUE3;
	wheel[12] = VALUE3;
	wheel[13] = VALUE3;
	wheel[14] = VALUE3;
	wheel[15] = VALUE4;
	wheel[16] = VALUE4;
	wheel[10] = VALUE4;
	wheel[18] = VALUE4;
	wheel[19] = VALUE5;
	wheel[23] = VALUE5;
	wheel[21] = VALUE2;
	wheel[24] = VALUE1;
 	wheel[20] = BANKRUPT;
	wheel[22] = LOSE_TURN;

	num = wheel[rand() % 25];
	return num;
}

//Create_Blank
string create_blank(string Text)
{
	string Str;


	for(int i = 0;i <Text.length(); i++)
	{
		Str += "-";
	}

	return Str;

}

//Guess a letter
int guess_letter(string Text, string &Str , string C)
{
	string Temp = "";
	int Count = 0;


	for(int i = 0; i < Str.length(); i++)
	{
		if(Text.substr(i,1) == C)
		{
			Temp += C;
			Count ++;
		}
		else
		{

			Temp += Str.at(i);


		}
	}
	Str = Temp;
	return Count;
}

int element_delete(Phrase Array[],int Count, int Num)
{
	// Local constants

	// Local variables
	int Temp = 0;							// Index to be deleted from the array

	/***************************** Start delete_game *****************************/

	// Call the search function
		// WHILE temp is less than Count
	 	while(Num < Count)
		{

			// Shift My_Games
			Array[Num] = Array[Temp + 1];

			// Increment Temp
			Num++;

		} // END WHILE

		// Decrement Count
		Count -= 1;


	// RETURN Count to main
	return Count;

} // END delete_game

void main_heading()
{
	// Local constants

	// Local variables

	/************************** Start heading **************************/

	// Clear screen
	system("cls");

	// Output heading
	cout << "\n\n\n";
 	cout << setw(48) << "----------------" << endl;
 	cout << setw(48) << "Wheel of Fortune" << endl;
 	cout << setw(48) << "----------------" << endl;
 	cout << "\n\n\n";

} // END heading
