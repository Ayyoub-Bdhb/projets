     +--------------------------------+
     |	       BOSSUS Quentin	      |
     |	       BOUDAHBA Ayyoub 	      |
     +--------------------------------+




     +--------------------------------+
     |	  Case (uppercase/lowercase)  |
     +--------------------------------+


Use of a case that takes into account whether the letter entered by the player is a 'r', 'R', 'l' or 'L', or 'y' and 'Y'.
If the player enters something else, the program will display an error message until it enters a valid letter.
If he can "accept" or "reject", the default answer (enters somethings else) will be "No".




     +--------------------------------+
     |	      Currency system 	      |
     +--------------------------------+


Creating a procedure to add gold to the player. 

The player can earn gold when he kills a monster or enters a room that contains it. 
So we use this procedure, which takes as parameter a amount of gold to add to the total of the player.




     +--------------------------------+
     |	   	Combat system 	      |
     +--------------------------------+


when the player enters a room where there is a monster :
a procedure taking as parameter a "fight file" is called to start the fight. 

As long as the monster or player has life, the fight continues. 

The player can :
-attack the monster and get a critical hit
-use an object (+5 hp and +2 damage)
-try to escape with a 20% chance of success. 

If he manages to escape, the fight stops; otherwise, the fight continues.




     +--------------------------------+
     |	   compile the program 	      |
     +--------------------------------+


	----------Windows---------- 

to compile the program under windows :
-you have to "gcc .\file_name.c"
-then "file_name.exe" and you execute file_name.exe.


	----------Linux----------

"gcc file_name.c -o file_name.ext"
execute "file_name.ext"

