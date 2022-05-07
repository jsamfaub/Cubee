# Cubee
![](https://github.com/jsamfaub/Cubee/blob/master/data/cubee%20logo.png)
Cubee (pronounced Kyu-bay) is an experimental game prototype made with C++ and SDL2 to test different features of SDL2.
I do plan to make it a somewhat full game some time in the future.
# Command Arguments
-np allows you to choose the number of players (currently only 1 and 2 are supported).
-l allows you to choose the level file from the data/levels/ folder.
Example: ./cubee -np 1 -l level1.lvl
# Custom Levels
You modify the level file in the data/levels/ folder to make a custom level.
's'=stars to collect
'g'=grass
'w'=wood
'l'=leaves
'#'=stone
'0'=nothing
'e'=enemy
'y'=yellow
The height and width of the level will be calculated automatically based on this file.
Have fun with this feature!

# Killing Enemies
READNEXTLINE(By punching, you can kill the enemies. They follow you slowly from a distance. They are stopped by walls and can't jump. Don't worry, they are unable to harm you in this version. Killing them awards you points.)
This is how it used to be in the old version. Currently, they only follow the player. i haven't yet implemented a combat system in this version of the game. I will eventually.

# Gameplay 
When all stars are collected, the game is over. "You Win!"
Watch this gameplay video:
https://youtu.be/NpsccqrJEf8

# Compiling
Simply type "make" in the command line and the MakeFile will take care of it.

# Player controls
For player 1, you move with wasd, jump with c and punch with v.For player 2, you move with the arrow keys, jump with p and punch with o. The other players' controls aren't yet configured.
No controls for other players.

# Other controls
q to quit
