# Cubee
![](https://github.com/jsamfaub/Cubee/blob/master/data/cubee%20logo.png)
Cubee (pronounced Kyu-bay) is an experimental game prototype made with C++ and SDL2 to test different features of SDL2.
I do plan to make it a somewhat full game some time in the future.
# Custom Levels
You modify the level1.lvl file in the data/levels/ folder to make a custom level.
Zeros ('0') represent empty spaces,
Hashtags ('#') represent blocks,
RGB ('r','g','b') represent blocks of different colors (red,green,blue).
Es ('e') represent enemies.
And Ns ('n') are used to seperate every horizontal line (so there's one at the end of every line except the last).
The height and width of the level will be calculated automatically based on this file.
Have fun with this feature!

# Killing Enemies
By punching, you can kill the enemies. They follow you slowly from a distance. They are stopped by walls and can't jump. Don't worry, they are unable to harm you in this version. Killing them awards you points.

# Gameplay video
https://www.youtube.com/watch?v=BH6g9s3bn-0

# Compiling
Simply type "make" in the command line and the MakeFile will take care of it.

# Player controls
For player 1, you move with wasd, jump with c and punch with v.For player 2, you move with the arrow keys, jump with p and punch with o. The other players' controls aren't yet configured.
No controls for other players.

# Other controls
q to quit
