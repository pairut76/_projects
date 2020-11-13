# _projects
creating algorithm for generating a random maze, also an algorithm for solving the maze

## Objective:
Finding a way to solve a maze using AI/Algorithm.The maze is randomnly generated - built on from a previous project. Random maze will be generated the program will run through and find a solution through the maze.

## Algorithm:
The program will run through the maze like a snake - with each step the program moves forward a random step is randomly generated for the next direction. A new random direction is generated with each step of the way, but when the program reaches a dead end ona randomly generated direction the program will retrace its step back to the previous spot/step. Once back in the previous step or spot a new random direction is generated, but it will not go to the dead end, as that location is omitted. This process continues until the program reaches the end. If there is no solution - the program would likely have exhausted all directions and step and would recoil all the way back to the start line.

## My Maze Solver:
Solver is located in the core/ folder. 
  
### Written in C++ 'mymazegenerator.hpp'
There are many classes contianed in the file. 
Random Direction - generates random direction for the next step
Visited - check if particular direction has already been visited
No Moves - Checks for dead end relieds on other functions to check for conditions of dead end
Move - recursive function that combines all the function above to generate the next step and make the next move
  program recursive returns to previous state if it hits a dead end
  
  
There are room for improvements for the program - a lot of the steps written can be simplified and placed in a simplier for loop condition. Steps can be written shorter to simplify readability and efficiency of the code.

## Conclusion:
There are no error conditions written - program cannot determine if there is a solution or not. If there is no solution the program will go back to the starting line.
  





