#include <iostream>

using namespace std;

int main_menu();

main()
{
	int number = 0;
	while(number != 4)
	{
		switch(number = main_menu())
		{
		case 1 : 
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
	
}


int main_menu()
{
	int choice = 0;
	cout << "1) Start new Game" << endl;
	cout << "2) Input new file" << endl;
	cout << "3) View rules" << endl;
	cout << "4) Quit" << endl;	
	cin >> choice;
	return choice;
}
