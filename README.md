# LUDO
This is the LUDO project guys

So I didn't use any rendering library, you just press Enter and play the game.
You may notice that the language is in French because I'm fluent in French so I used it in the gameplay and some english in the code (cause french name for variable and functions are too long).

The classic mode is the ludo you used to play on phone and the "No Mercy" mode is a new mode where the base are shared so a player can be hunted until he reaches the center.

Some explanation about the "No Mercy" mode:
-The bases are shared
-The last straight line is not a safe place anymore
-There are two kinds of star: the white one and the purple one
-If a player stops at a purple star another player is teleported behind him at the corner(that's the summon function in the code for)
-There is a new number on the dice: the "0"
-It only supports 4 players

I think that's all.

And again I'm so sorry for the lack of comment in the code.

And this is the fomat of the savedata for the curious
4 0 => Number of player and the current turn
0 0 0 0 => Score of each player
4 4 4 4 0 => The classement of each player if the player haven't won yet the his classement is the number of player
 the "0" is the actual index of the classement
10 1 => coordinates of a pawn of the player
1 1
1 10
10 10
13 1
4 1
4 10
13 10
10 4
1 4
1 13
10 13
13 4
4 4
4 13
13 13
Time: Feb 18 2026, 16:13:48
