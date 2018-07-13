# filler
The goal of this project is to code a player for the Filler game.
Ruby virtual machine and default players are given in resources folder.
Complete project description can be seen here: https://github.com/akorzhak/filler/blob/master/filler.en.pdf

Project algorithm is based on well-known (or not) Manhattan distance algorithm.

To run the project:
1. make
2. ./resources/filler_vm -f resources/maps/map00 -p1 ./akorzhak.filler -p2 ./resources/players/abanlin.filler
(maps and players can be changed)
3. Append " | ./visual/v2" to the step 2. to see some elementary bash script based visualization.
4. make fclean
