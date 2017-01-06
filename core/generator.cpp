

//Pairut Dumkuengthanant
//ID: 64856070
//ics 46

#include <iostream>
#include "mymazegenerator.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,mymazegenerator, "My_Generator (Required)");


void mymazegenerator::generateMaze(Maze& maze)
	{
		not_visited=(maze.getHeight())*(maze.getWidth());
		//Maze x_maze=maze.clone();
		_h=maze.getHeight();
		_w=maze.getWidth();
		_refresh(maze);
		
		//bool k=Direction::right==Direction::right;
		//std::cout<<k<<std::endl;
		//std::cin>>"start: ";
		//std::cout<<"refresh complete"<<std::endl;
		new_vect(maze);
		//std::cout<<"new vector created"<<std::endl;
	//while(not_visited!=0)
	//{
		move(0,0,maze);

		//std::cout<<not_visited<<std::endl;
	//}
		
		//std::cout<<"done!"<<std::endl;
		
		
		
		
	}
//mymazegenerator::mymazegenerator();
//mymazegenerator::~mymazegerator()

//void generateMaze(Maze& maze)