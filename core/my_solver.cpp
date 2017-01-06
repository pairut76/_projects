


//Pairut Dumkuengthanant
//ID: 64856070
//ics 46
#include <iostream>
#include "mymazesolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "MazeSolution.hpp"
#include <iomanip>
//#include "MazeSolver.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, mymazesolver, "my_solver(Required)");

//mymazesolver::~
void mymazesolver::solveMaze(const Maze&maze, MazeSolution& mazeSolution)
	{

		mazeSolution.restart();
		std::pair<int, int> start;
		h_=mazeSolution.getHeight();
		w_=mazeSolution.getWidth();
		//not_visited=h_*w_;
		start = mazeSolution.getStartingCell();
		//std::pair start;
		new_vect(mazeSolution);
		
		
		std::cout<<std::setfill('-')<<std::setw(80)<<"-"<<std::endl;
		//Direction dir=rand_dir();
		solver(start.second, start.first,maze, mazeSolution);
		
	}

	

		
	
//mymazesolver::mymazesolver();
//mymazesolver::~mymazesolver();