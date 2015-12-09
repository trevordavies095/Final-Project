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
 
 #include <iostream>
 #include <fstream>
 using namespace std;
 
 
string update_phrase(string Game_Phrase, string Guessed_Letter, string Current_Phrase)
{
	//Global Constants
	const string Space = " ";			//stores a space
	
	//Global Variables
	string Temp = "";					//Holds the phrase as it updates
	
	for(int i = 0; i < Game_Phrase.length(); i++)//counter for checking all characters
	{
		if(Current_Phrase.substr(i,1) != space)//If index is not equal to a space
		{
			temp += Current_Phrase.substr(i,1);//Add that index character to temp
		}
		else if(Current_Phrase.substr(i,1) == space)//If index is equal to a space
		{
			if(Game_Phrase.substr(i,1) == Guessed_Letter)//If index is equal to guessed letter
			{
				temp += Game_Phrase.substr(i,1);//Add that index character to temp
			}
			else//If it's not eaual to the guessed letter
			{
				temp += space;//Add that index character to temp
			} 
		}
		else
		{
			temp += " ";
		}
	}
	return temp;
	
}//End update_phrase
