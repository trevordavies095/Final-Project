# Final-Project
Make a program, similar to the games Wheel of Fortune or Hangman. At the start of the 
program, there should be a start menu giving the user the option of:

Start a new game

Input a new file of phrases

View the rules and odds

Quit

When the user chooses to start a new game, give them the option of playing with 1-4 players.  
After selecting how many players, the user should be able to name each player.  The players 
will be given an option to spin the wheel, buy a vowel, and solve the puzzle.

The players will “spin the wheel” and win prizes at the following rates:

$250 - 5/25

$500 - 5/25

$750 - 5/25

$1000 - 4/25

$1500 - 3/25

Lose a turn - 2/25

Bankrupt - 1/25

After the user’s prize value is determined, he will enter a letter.  If the letter has already been 
guessed, the player will receive no money won or lost, and the next player will go. If the letter 
has not been guessed, the user will receive the prize money * n (where n is the number of times 
that letter shows up in the phrase).  If the user spins Lose a turn, the next player will go and the 
user will not be allowed to select a letter.  If the user spins Bankrupt, the user’s round score will 
go to zero, and the entire game score will be unaffected.  

If the player chooses buy a vowel, he will be charged a one time fee of $250, and if he correctly 
guesses a vowel he will be allowed to spin, buy, or solve again. If he incorrectly chooses his turn 
is then over. 

If the player chooses to solve the puzzle, and correctly solves the puzzle, his round score will 
then be added to his game score. The other players who did not solve the puzzle will have their 
round score reset to zero and nothing added to their game score. If the puzzle is not solved, the 
players turn is then over.

The user will be allowed to continue to play more rounds until they are finished with the game.  
At the end of the game, they may start a new game at round one. 

If the user inputs a file of phrases, those phrases will be used in the game.  If the user does not 
add any files to the game, there will be a defult.txt file with the program that the game will use.
