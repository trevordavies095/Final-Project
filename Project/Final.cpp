/**************************************************************************
*Function Name      :    Final
*Author             :    Joe McCarthy, Tyler Myers, Loren Davies
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*begin main
*	Call main heading
*	call the main menu
*	WHILE Choice != QUIT
*		SWITCH CHOICE
*			CASE They pick start a new game
*				IF there's no file entered
*					Enter default file and set File_Entered to true
*				END IF
*				Call main heading
*				Get number of players from the user
*				Get the players names
*				Call main heading
*				WHILE user chooses to continue to another round
*					Get a new random phrase
*					Delete the phrase
*					Make the blank spaces board
*					WHILE the puzzle isn't solved
*						Set the players names for the round array
*						FOR every player
*							WHILE players turn is up
*								IF turn = 0
*									IF i+1 = Number of players
*										Turn = 1
*									END IF
*									ELSE
*										Next player turn = 1
*									END IF
*								END IF
*								Call heading
*								Output board and guessed letters
*								Call turn menu
*								SWITCH Turn_Choice
*									CASE they chose to spin
*										Call spin wheel, output points
*										IF spin is bankrupt
*											Next players turn
*										END IF
*										IF player's turn
*											
*										END IF
*										ELSE
*											Input user's guess
*											WHILE they enter a vowel
*												Input user's guess
*											END WHILE
*											Add letter to guessed letters
*											Call letter_value
*											IF letter_value is 0
*												Next player's turn
*											END IF
*											ELSE
*												Add spin value to score
*											END IF
*										END IF
*									END CASE
*									CASE they buy a vowel
*										IF score < 250 
*											Output error message
*										ELSE
*											Input vowel to buy
*											Decrememnt score
*											Get letter value
*											Add to guessed letter
*										END IF
*									END CASE
*									CASE they choose to solve puzzle
*										Input guess
*										IF guess is correct
*											Set solved to ture
*											Add score to score
*											Next player's turn
*										END IF
*									END CASE
*								END SWITCH
*							END WHILE
*						END FOR
*					END WHILE
*					Ask if they want to play again
*				END WHILE
*			END CASE
*			CASE insert file
*				Input file name
*				Add to Phrase_Count
*				Set File_Entered to true
*			END CASE
*			CASE show rules
*				Output rules
*			END CASE
*		END SWITCH
*		Show main menu
*	END WHILE
*end main
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
string init_phrase(string, string);
string update_phrase(string, string, string);



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
	string Temp1,Temp2 = "";
	string Current_Phrase = "";
	string Guessed_Letters;
	string Player_Guess;
	bool Round_Continue = true;	// The player chooses to continue to another round
	bool File_Entered = false;	// Becomes true if the user enters a file
	bool Solved = false;

	string Display_Phrase;


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

					Solved = false;

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
								// IF turn = 0
								if (Round_Array[i].Turn == 0)
								{
									// IF i+1 = Number of players
									if((i+1) == Num_Players)
									{
										// Turn = 1
										Round_Array[0].Turn = 1;
									}
									else
									{
										// Next player turn = 1
										Round_Array[i+1].Turn = 1;
									}
								}

								// Call heading
								heading(Round_Array, Num_Players);

								// Output board and guessed letters
								cout << setw(40) << "Phrase: " << Current_Phrase << endl;
								cout << setw(40) << "Guessed Letters: " << Guessed_Letters << endl;

								// Turn menu
								Turn_Choice = turn_menu();
								switch(Turn_Choice)
								{
									// Sping the wheel
									case 1:
										
										// Call spin wheel
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
											else
											{
												i = 0;
												Round_Array[i].Turn += 1;
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
											else
											{
												i = 0;
												Round_Array[i].Turn +=1;
											}
											break;

										}// END IF
										else
										{
											// Input guess
											cout << "\n\n";
											cout << "Input your guess: ";
											cin >> Player_Guess;
											
											// If they enter a vowel
											while(Player_Guess == "a" || Player_Guess == "e" || Player_Guess == "i" || Player_Guess == "o" || Player_Guess == "u")
											{
												cout << "You have to buy a vowel!" << endl;
												cout << "\n\n";
												
												cout << "Input your guess: ";
												cin >> Player_Guess;
											}
											
											// Add guess to guessed letters
											Guessed_Letters += Player_Guess + ", ";
											
											// Call letter_value
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
													break;
												}

											}// END IF
											else
											{
												Round_Array[i].Score += Spin_Value*Letter_Value;
												Round_Array[i].Turn = 1;
												break;
											}// END IF


										}//END ELSE
										break;

									case 2:
										if(Round_Array[i].Score < 250)
										{
											cout << " You don't have enough to buy a vowel" << endl;
										}
										else
										{
											// Input vowel to buy
											cout << "Enter a vowel for $250: ";
											cin >> Player_Guess;
											
											// Decrememnt score
											Round_Array[i].Score -= 250;
											
											// Get letter value
											Letter_Value = guess_letter(Game_Phrase.Text , Current_Phrase , Player_Guess);
											
											// Add to guessed letter
											Guessed_Letters += Player_Guess + ", ";
										}
										
										break;


									case 3:
										
										// Input guess
										cout << "\n\n";
										cin.get();
										cout << setw(40) << "Category: " << Game_Phrase.Category << endl;
										cout << setw(40) << "Phrase: " << Current_Phrase << endl;
										cout << setw(40) << "Your answer: ";
										getline(cin, Player_Guess);
										for(int j = 0; j < Player_Guess.length(); j++)
										{
											Temp1 += toupper(Player_Guess.at(j));
										}
										for(int k = 0; k < Game_Phrase.Text.length(); k++)
										{
											Temp2 += toupper(Game_Phrase.Text.at(k));
										}

										// IF guess is correct
										if(Temp1 == Temp2)
										{
											Solved = true;
											Player_Array[i].Score += Round_Array[i].Score;
											Round_Array[i].Turn = 0;
											if(Num_Players == 1)
												i = Num_Players - 1;
											else
												i = Num_Players + 2;



										}


								}//END TURN_CHOICE SWITCH

							}// END TURN WHILE
						}//END TURN SYSTEM FOR


					}// END SOLVED WHILE


					// Play again?
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
				
				// Enter file name
				cout << "Enter a file name: ";
				cin >> File_Name;
				
				// Add to Phrase_Count
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

/**************************************************************************
*Function Name      :    main_menu
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main_menu
*	Output the choices
*	Input choices
*	WHILE choice is invalid
*		Output the choices
*		Input choices
*	END WHILE
*	Return choice
*END main_menu
**************************************************************************/

// Main menu
int main_menu()
{
	// Local constants
	
	// Local variables
	int Choice = 0;
	
	/**********************************************/
	
	// Ouput the choices
	cout << setw(49) << "1) Start new game" << endl;
	cout << setw(49) << "2) Input new file" << endl;
	cout << setw(45) << "3) View rules" << endl;
	cout << setw(40) << "4) Quit " << endl;
	cout << setw(36) << "--> ";
	
	// Input choice
	cin >> Choice;
	
	// WHILE choice is invalid
	while(Choice < 1 && Choice > 4)
	{
		cout << setw(49) << "1) Start new game" << endl;
		cout << setw(49) << "2) Input new file" << endl;
		cout << setw(45) << "3) View rules" << endl;
		cout << setw(40) << "4) Quit " << endl;
		cout << setw(36) << "--> ";
	}
	
	// Return Choice
	return Choice;
}

/**************************************************************************
*Function Name      :    turn_menu
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main_menu
*	Output the choices
*	Input choices
*	WHILE choice is invalid
*		Output the choices
*		Input the choice
*	END WHILE
*	Return choice
*END main_menu
**************************************************************************/

//Turn menu
int turn_menu()
{
	// Local constants
	
	// Local variables
	int Choice = 0;
	
	/**********************************************/
	
	// Output the choices
	cout << "\n\n\n";
	cout << setw(49) << "1) Spin the wheel" << endl;
	cout << setw(46) << "2) Buy a vowel" << endl;
	cout << setw(51) << "3) Solve the puzzle" << endl;
	cout << setw(36) << "--> ";
	
	// Input the choice
	cin >> Choice;
	
	// WHILE choice is invalid
	while(Choice < 1 && Choice > 3)
	{
		// Output the choices
		cout << "\n\n\n";
		cout << setw(49) << "1) Spin the wheel" << endl;
		cout << setw(46) << "2) Buy a vowel" << endl;
		cout << setw(51) << "3) Solve the puzzle" << endl;
			cout << setw(36) << "--> ";
		
		// Input the choice
		cin >> Choice;
	}
	
	// Return choice
	return Choice;
}

/**************************************************************************
*Function Name      :    heading
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main
*
*END main
**************************************************************************/

void heading(Player Array[], int Num)
{
	// Local constants
	
	// Local variables
	
	/**********************************************/
	
	switch(Num)
	{
		case 1:
			cout << setw(30) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score <<  endl;
			break;
		case 2:
			cout << setw(30) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(30) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score <<  endl;
			break;
		case 3:
			cout << setw(30) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(30) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score << endl;
			cout << setw(30) << Array[2].Name << "'s ";
			cout << "score: " << Array[2].Score <<  endl;

			break;
		case 4:
			cout << setw(30) << Array[0].Name << "'s ";
			cout << "score: " << Array[0].Score << endl;
			cout << setw(30) << Array[1].Name << "'s ";
			cout << "score: " << Array[1].Score << endl;
			cout << setw(30) << Array[2].Name << "'s ";
			cout << "score: " << Array[2].Score <<  endl;
			cout << setw(30) << Array[3].Name << "'s ";
			cout << "score: " << Array[3].Score <<  endl;
			break;
		default:
			cout << "Invalid Input";
	}
}

/**************************************************************************
*Function Name      :    next_round
*Author             :    Joe McCarthy, Tyler Myers, Loren Davies
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main
*
*END main
**************************************************************************/


bool next_round()
{
	// Local constants
	
	// Local variables
	int Choice;
	
	/*****************************************************/
	
	cout << "Would you like to play another round? " << endl;
	cout << "1) Yes " << endl;
	cout << "2) No " <<endl;
	cout << "-->  " ;
	cin >> Choice;
	
	while (Choice > 2 && Choice < 1)
	{
		cout << "Would you like to play another round? " << endl;
		cout << "1) Yes " << endl;
		cout << "2) No " <<endl;
		cout << "-->  " ;
		cin >> Choice;
	}
	
	
	if(Choice == 1)
	return true;
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
 *			Input Category
 *			Get rid of space at the end
 *			Input Phrase Text
 *			Get rid of the space at the start
 *			Add phrase to array
 *			Increment count
 *		END WHILE
 *		Return Count
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

			// Add phrase to Array
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
/**************************************************************************
*Function Name      :    spin_wheel
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main
*
*END main
**************************************************************************/

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
	
	/******************************************************/

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

/**************************************************************************
*Function Name      :    create_blank
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN create_blank
*	FOR every character in the string
*		Add a - to Str
*	END FOR
*	Return Str
*END create_blank
**************************************************************************/

string create_blank(string Text)
{
	// local constants
	
	// Local variables
	string Str;
	
	/******************************************************/
	
	// For every character in the string
	for(int i = 0;i <Text.length(); i++)
	{
		// Add a -
		Str += "-";
	}

	return Str;

}

/**************************************************************************
*Function Name      :    guess_Letter
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN guess_letter
*
*END guess_letter
**************************************************************************/

int guess_letter(string Text, string &Str , string C)
{
	// Local constants
	
	// Local variables
	string Temp = "";
	int Count = 0;
	
	/*****************************************************/

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

/**************************************************************************
*Function Name      :    element_delete
*Author             :
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main
*
*END main
**************************************************************************/

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

/**************************************************************************
*Function Name      :    main_heading
*Author             :    Loren Davies
*Date               :    12/17/2015
*Course/Section     :    CSC 263 - 001
*Program Description:
*
*BEGIN main
*
*END main
**************************************************************************/

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
