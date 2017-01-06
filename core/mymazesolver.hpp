

//Pairut Dumkuengthanant
//ID: 64856070
//ics 46
#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP


#include <iostream>
#include <random>
#include "MazeSolver.hpp"
#include <vector>
#include "Maze.hpp"
#include "MazeSolution.hpp"

//MazeSolver::~MazeSolver();
class mymazesolver : public MazeSolver
{
	std::vector<std::vector<bool>> vect;
	//std::vector<std::pair<int, int>> p_vect;
	int h_, w_;
	
	void print_visits()
	{
		for(int i=0; i<h_;i++)
		{
			
			for(int j=0;j<w_;j++)
			{
				std::cout<<vect[i][j];
			}
			std::cout<<"\n";
		}
	}

	void visited(int row, int col)
	{
		//not_visited-=1;
		vect[row][col]=true;
	}
	void new_vect(MazeSolution& maze)
	{
		
		//not_visited=(maze.getWidth())*(maze.getWidth());
		std::vector<std::vector<bool>> v(maze.getHeight(),std::vector<bool>(maze.getWidth()));

		for(int i=0; i<maze.getHeight();++i)
		{	
			std::vector<bool> subvect;
			v.push_back(subvect);
			for(int j=0; j<maze.getWidth();++j)
			{
				v[i].push_back(j);
				v[i][j]=false;
			}

		}
		vect=v;

		//vect[0][0]=true;
	}
	Direction _convert(int x)
	{
		switch(x)
		{
			case(0): //in boundaries
				return Direction::up;
			case(1): 
				return Direction::right;
			case(2): 
				return Direction::down;
			case(3): 
				return Direction::left;
			default: return Direction::right;
		}
	}
	void update_coor(int& v, int& w, Direction dr)
	{
		//std::cout<<"update_coor: "<<v<<"	"<<w<<std::endl;
		switch(dr)
		{
			case(Direction::up): 
				//std::cout<<"up"<<std::endl;
				//if(in_bounds(v-1,w))
					v-=1;
				break;
			case(Direction::right): 
				//std::cout<<"right"<<std::endl;
				//if(in_bounds(v,w+1))
					w+=1;
				break;
			case(Direction::down): 
				//std::cout<<"down"<<std::endl;
				//if(in_bounds(v+1,w))
					v+=1;
				break;
			case(Direction::left): 
				//std::cout<<"left"<<std::endl;
				//if(in_bounds(v,w-1))
					w-=1;
				break;
		}
		return;
	}
	Direction rand_dir()
	{
		std::random_device device;
		std::default_random_engine engine{device()};
		std::uniform_int_distribution<int> distribution{0,3};
		return _convert(distribution(engine));
	}
	bool in_bounds(int s, int t)
	{
		return s>=0&& t>=0 && s<h_ && t<w_;
	}

	bool _stuck(int a, int b, const Maze& m)//checks if cur_pos surrounded by 3 walls (trapped)
	{
		int count=0;
		if(m.wallExists(b,a,Direction::up))
			count++;
		if(m.wallExists(b,a,Direction::right))
			count++;
		if(m.wallExists(b,a,Direction::down))
			count++;
		if(m.wallExists(b,a,Direction::left))
			count++;

		return count==3;
	}
	Direction check_wall(int c_x, int c_y, const Maze& m)//returns back direction without wall
	{
		if(!m.wallExists(c_y, c_x, Direction::up))
			return Direction::up;
		if(!m.wallExists(c_y, c_x, Direction::right))
			return Direction::right;
		if(!m.wallExists(c_y, c_x, Direction::left))
			return Direction::left;
		if(!m.wallExists(c_y, c_x, Direction::down))
			return Direction::down;
		return Direction::right;

	}
	bool check_dir(int a, int b,Direction d)
	{
		switch(d)
		{
			case(Direction::up): return vect[a-1][b]==true;
			case(Direction::down): return vect[a+1][b]==true;
			case(Direction::right): return vect[a][b+1]==true;
			case(Direction::left): return vect[a][b-1]==true;
		}
	}
bool no_moves(int s, int t)
	{
		int count=0;
		//upper

		//std::cout<<"getting check for no more possible moves"<<std::endl;
		//std::cout<<s<<"	"<<t<<std::endl;
		if(s==0&&t==0)//corner left
		{
			if(check_dir(s,t,Direction::down))//below
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;
			
				//std::cout<<"no 1 "<<count<<std::endl;
				return count==2;
			
		}
		count=0;
		if(s==0&&t==(w_-1))//corner right
		{
			if(check_dir(s,t,Direction::down))//down
				count++;
			if(check_dir(s,t,Direction::left))//left
				count++;
			
				//std::cout<<"no 2 "<<count<<std::endl;
				return count==2;
		}
		count=0;
		//bottom
		if((s==h_-1)&&t==0)//corner left 
		{
			if(check_dir(s,t,Direction::up))//up
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;
			
				//std::cout<<"no 3 "<<count<<std::endl;
				return count==2;
			
		}
		count=0;
		if((s==h_-1)&&(t==w_-1))//corner right bottom
		{
			if(check_dir(s,t,Direction::up))//up
				count++;
			if(check_dir(s,t,Direction::left))//left
				count++;
			//std::cout<<"no 4 "<<count<<std::endl;
			return count==2;
		}

		count=0;

		if(s==0||s==h_-1)//first row & last row
		{
			if(check_dir(s,t,Direction::left))//left
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;

			if(s==h_-1)
			{
				if(check_dir(s,t,Direction::up))
					count++;
			}
			if(s==0)
			{
				if(check_dir(s,t,Direction::down))
					count++;
			}
			//std::cout<<"no 5 "<<count<<std::endl;
			return count==3;
		}
		count=0;
		if(t==0||(t==w_-1))//first & last column
		{
			if(check_dir(s,t,Direction::down))//check below
				count++;
			if(check_dir(s,t,Direction::up))//check up
				count++;
			if(t==0)
			{
				if(check_dir(s,t,Direction::right))
					count++;
			}
			if(t==w_-1)
			{

				if(check_dir(s,t,Direction::left))
					count++;
			}
			
				//std::cout<<"no 5.5 "<<count<<std::endl;
				return count==3;
			
		}

		count=0;
		if(in_bounds(s-1,t)&&in_bounds(s+1,t))
		{
			if(check_dir(s,t,Direction::up))//check up
				count++;
			if(check_dir(s,t,Direction::down))//check below
				count++;
		}
		if(in_bounds(s,t-1)&&in_bounds(s,t+1))
		{
			if(check_dir(s,t,Direction::left))//left
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;
		}
		
		
			//std::cout<<"no 6"<<count<<std::endl;
			return count==4;
		

		return false;
	}	

	//void cancel_visit(int s, int t)
	//{
		//vect[s][t]=false;
	//}
	void solver(int x, int y,const Maze& m, MazeSolution& ms)
	{


		std::pair<int,int> cur_cell;
		
		std::pair<int, int> stop;
		//stop = ms.getEndingCell();
		//std::cout<<"ending: "<<stop.second<<"	"<<stop.first<<std::endl;
		int dx, dy;
		if(ms.isComplete())
			{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				return;
			}
		Direction dir=rand_dir();
		dx=x;
		dy=y;
		//std::cout<<"current position: "<<x<<"	"<<y<<std::endl;
		//std::cout<<"proposed position: "<<std::endl;
		update_coor(dx,dy,dir);
		//std::cout<<dx<<"	"<<dy<<std::endl;
		//print_visits();
		
			while(!in_bounds(dx,dy))
			{
				if(ms.isComplete())
				{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				break;
				}
				//std::cout<<"generating new coor"<<std::endl;
				dir=rand_dir();
				dx=x;
				dy=y;
				update_coor(dx,dy,dir);

			}
			if(ms.isComplete())
			{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				return;
			}
			while(m.wallExists(y,x,dir)||vect[dx][dy]==true)
			{
				
				//std::cout<<"Hit wall"<<std::endl;

				if(ms.isComplete())
				{
					x=stop.second;
					y=stop.first;
					//std::cout<<"destination reached"<<std::endl;
					break;
				}
				dir=rand_dir();
				dx=x;
				dy=y;
				update_coor(dx,dy,dir);

				if(_stuck(x, y, m)&&vect[x][y]!=false)
					break;
				if(no_moves(x,y)&&vect[x][y]!=false)
					break;
			}
			if(ms.isComplete())
			{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				return;
			}
			if(!m.wallExists(y,x,dir)&&vect[dx][dy]==false)
			{
				//std::cout<<"VALID"<<std::endl;
				ms.extend(dir);
				visited(x,y);
				update_coor(x,y,dir);
				visited(x,y);
				
				solver(dx, dy, m, ms);
			
			}
				if(ms.isComplete())
			{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				return;
			}
					
				ms.backUp();
				cur_cell=ms.getCurrentCell();
				y=cur_cell.first;
				x=cur_cell.second;
	
				
				//dir=check_wall(x,y,m);
				//update_coor(x,y,dir);
				//std::cout<<"went back to: "<<x<<"	"<<y<<std::endl;
				//solver(x, y, m,ms);
				//solver(x,y,m,ms);
			
			if(ms.isComplete())
			{
				x=stop.second;
				y=stop.first;
				//std::cout<<"destination reached"<<std::endl;
				return;
			}
			
			solver(x, y, m,ms);
			
		}


	void solveMaze(const Maze&maze, MazeSolution& mazeSolution);
	
	//}
	
};

#endif // MYMAZESOLVER_HPP