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

 // Structures
 struct phrase
 {
 	string Category;
 	string Phrase;
 };
 
 // Global constants
 
 // Global variables
 
 int main()
 {
 	// Local constants
	const int SIZE = 30;
 	
 	// Local variables
 	phrase Array[SIZE];
 	string File_Name;					// File name the user inputs
	string Current_Line;				// Line being read
	phrase phrase;
	ifstream fs;						// Input stream
	int Count = 0;
 	
 	/****************************** start insert_file ******************************/
 	
 	// Input file name
	cout << "File name: ";
	cin >> File_Name;
	
	// Open file
	fs.open(File_Name.c_str());
	
	// IF there's a problem opening the file
	if(fs.fail())
	{
		// Output error message
		cout << "File DNE";
	}
	
	// ELSE file did open properly
	else
	{
		// Read first line, but do nothing with it
		getline(fs, Current_Line);
		
		// WHILE it isn't the end of the file
		while(!fs.eof())
		{
			// Input Category
			getline(fs, phrase.Category, '-');
			
			phrase.Category.erase(phrase.Category.length()-1);
			
			// Input Phrase
			getline(fs, phrase.Phrase, '\n');
			
			phrase.Phrase.erase(0,1);
			
			Array[Count] = phrase;
			
			Count++;
		}
	}
 }
