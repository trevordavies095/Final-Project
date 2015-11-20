#include <iostream>

using namespace std;

int main_menu();

main()
{
	int Number = 0;
	int Num_Players = 0;
	while(Number != 4)
	{
		Number = main_menu();
		switch(Number)
		{
		case 1 :
			cout << "How many players: ";
			cin >> Num_Players;
			break;
		case 2 :
			break;
		case 3 :
			break;
		case 4 :
			break;
		default :
			break;
	   }
	}
	cout << "There are " << Num_Players << " players";
	
}


int main_menu()
{
	int Choice = 0;
	cout << "1) Start new Game" << endl;
	cout << "2) Input new file" << endl;
	cout << "3) View rules" << endl;
	cout << "4) Quit" << endl;	
	cin >> Choice;
	return Choice;
}

string enter_players()
{
	string Name = "";
	cout << "Enter Player Name: ";
	return Name;
	
}
