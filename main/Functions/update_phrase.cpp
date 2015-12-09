/**************************************************************************
 *Function Name      :    update_phrase
 *Author             :    Tyler Myers
 *Date               :    12/9/2015
 *Course/Section     :    CSC 263 - 001
 *Program Description:    Changes the current phrase
 *
 *BEGIN update_phrase
 *	FOR(i less then game phrase count)
 *		IF(index of current phrase is not equal to a space)
 *			add index character to temp
 *		ELSE IF(index of current phrase is equal to a space)
 *			IF(index of game phrase is equal to guessed letter
 *				add index character to temp
 *			else
 *				add a space to temp
 *			END IF
 *		else
 *			add a space to temp
 *		END IF
 *	END FOR
 *END insertFile
 **************************************************************************/
 
 #include <iostream>
 #include <fstream>
 using namespace std;
 
 
string update_phrase(string Game_Phrase, string Guessed_Letter, string Current_Phrase)
{
	//Global Constants
	const string SPACE = " ";			//stores a space
	
	//Global Variables
	string Temp = "";					//Holds the phrase as it updates
	
	for(int i = 0; i < Game_Phrase.length(); i++)//counter for checking all characters
	{
		if(Current_Phrase.substr(i,1) != SPACE)//If index is not equal to a space
		{
			Temp += Current_Phrase.substr(i,1);//Add that index character to temp
		}
		else if(Current_Phrase.substr(i,1) == SPACE)//If index is equal to a space
		{
			if(Game_Phrase.substr(i,1) == Guessed_Letter)//If index is equal to guessed letter
			{
				Temp += Game_Phrase.substr(i,1);//Add that index character to temp
			}
			else//If it's not eaual to the guessed letter
			{
				Temp += SPACE;//Add that index character to temp
			} 
		}
		else
		{
			Temp += " ";
		}
	}
	return Temp;
	
}//End update_phrase
