/*
 * Player.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: JosephMcCarthy
 */

#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;


// Parameter instances

Player::Player()
{
	Name = "Player";
	Score = 0;
	Turn = 1;
}

Player::Player(string Str)
{
	Name = Str;
	Score = 0;
}

Player::Player(int Num)
{
	Name = "Player";
	Score = Num;

}

Player::Player(string Str, int Num)
{
	Name = Str;
	Score = Num;
}

Player::Player(int Num, int Tur)
{
	Score = Num;
	Turn = Tur;
}

Player::Player(string Str, int Num, int Tur)
{
	Name = Str;
	Score = Num;
	Turn = Tur;
}
//Setters
void Player::set_name(string Str)
{
   Name = Str;
}

void Player::set_score(int Num)
{
   Score = Num;
}

void Player::set_turn(int Tur)
{
   Turn = Tur;
}
//Getters
string Player::get_name()
{
   return Name;
}

int Player::get_score()
{
   return Score;
}

int Player::get_turn()
{
   return Turn;
}
