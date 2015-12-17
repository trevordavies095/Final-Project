/*
 * Player.h
 *
 *  Created on: Nov 20, 2015
 *      Author: JosephMcCarthy
 */
#include <iostream>
#include <iomanip>
using namespace std;
#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
	public:
		//  Member functions
		//  Constructors
		Player();
		Player(string);
		Player(int);
		Player(string, int);
		Player(int, int);
		Player(string, int, int);

		//  Set name and score
		void set_name(string);
		void set_score(int);
		void set_turn(int);

		//  Accessors
		string get_name();
		int get_score();
		int get_turn();

		string Name;
		int Score;
		int Turn;

	private:

};

#endif // PLAYER_H_
