

//Pairut Dumkuengthanant
//ID: 64856070
//ics 46


#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP

#include <iostream>
#include "MazeGenerator.hpp"
#include <vector>
#include "Maze.hpp"
#include <random>
#include "Direction.hpp"
//#include "storage.hpp"

class mymazegenerator : public MazeGenerator
{
public:
	
	int x=0, y=0;
	int not_visited;
	int _h, _w;
	//Maze* x_maze;

	std::vector<std::vector<bool>> vect;

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
	Direction rand_dir()
	{
		std::random_device device;
		std::default_random_engine engine{device()};
		std::uniform_int_distribution<int> distribution{0,3};
		return _convert(distribution(engine));
	}

	void new_vect(Maze& maze)
	{
		
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
	void _refresh(Maze& m)
	{
		m.removeAllWalls();
		m.addAllWalls();
	}
	
	void visited(int row, int col)
	{
		//not_visited-=1;
		vect[row][col]=true;
	}
	bool check_valid(int x, int y,Direction d)
	{
		
		if(x==0&&d==Direction::up)
			return false;

		if(y==0&&d==Direction::left)
			return false;

		if(x==(_h-1)&&d==Direction::down)
			return false;

		if(y==(_w-1)&&d==Direction::right)
			return false;

		
		return true;
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
	void print_visits()
	{
		for(int i=0; i<_h;i++)
		{
			
			for(int j=0;j<_w;j++)
			{
				std::cout<<vect[i][j];
			}
			std::cout<<"\n";
		}
	}
	bool in_bounds(int s, int t)
	{
		return s>=0&& t>=0 && s<_h && t<_w;
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
		if(s==0&&t==(_w-1))//corner right
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
		if((s==_h-1)&&t==0)//corner left 
		{
			if(check_dir(s,t,Direction::up))//up
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;
			
				//std::cout<<"no 3 "<<count<<std::endl;
				return count==2;
		
		}
		count=0;
		if((s==_h-1)&&(t==_w-1))//corner right bottom
		{
			if(check_dir(s,t,Direction::up))//up
				count++;
			if(check_dir(s,t,Direction::left))//left
				count++;
			//std::cout<<"no 4 "<<count<<std::endl;
			return count==2;
		}

		count=0;

		if(s==0||s==_h-1)//first row & last row
		{
			if(check_dir(s,t,Direction::left))//left
				count++;
			if(check_dir(s,t,Direction::right))//right
				count++;

			if(s==_h-1)
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
		if(t==0||(t==_w-1))//first & last column
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
			if(t==_w-1)
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
		
	}	

	void move( int dx, int dy,Maze& maze)
	{	
		//proposed position:
		Direction dir=rand_dir();
		int px, py;
		//Direction old_dir=dir;
		//dir=rand_dir();
		px=dx;
		py=dy;
		//std::cout<<"cur_pos: "<<dx<<"	"<<dy<<std::endl;
		//std::cout<<"proposed position:"<<std::endl;
		update_coor(px, py,dir);
		//std::cout<<px<<"	"<<py<<std::endl;
		//print_visits();
		//std::cout<<not_visited<<std::endl;

	//while(not_visited!=0){
		while(!in_bounds(px,py))
		{
			//std::cout<<"not in bounds in while"<<std::endl;
			dir=rand_dir();
			px=dx;
			py=dy;
			update_coor(px,py,dir);
		}
		if(not_visited==0)
			return;
		
				if(check_valid(dx,dy,dir)&&vect[px][py]==false)
				{


					if(dir==Direction::right)
					{
						//std::cout<<"VALID"<<std::endl;
						maze.removeWall(dy,dx,dir);
						visited(dx,dy);
						dy+=1;
						visited(dx,dy);
						//update_coor(x,y,dir);

						//visited(dx,dy);
						not_visited-=1;
						move(dx, dy,maze);
					}
					if(dir==Direction::up)
					{
						//std::cout<<"VALID"<<std::endl;
						maze.removeWall(dy,dx,dir);
						visited(dx,dy);
						dx-=1;
						visited(dx,dy);
						//update_coor(x,y,dir);

						//visited(dx,dy);
						not_visited-=1;
						move(dx, dy,maze);
					}
					if(dir==Direction::down)
					{
						//std::cout<<"VALID"<<std::endl;
						maze.removeWall(dy,dx,dir);
						visited(dx,dy);
						dx+=1;
						visited(dx,dy);
						//update_coor(x,y,dir);

						//visited(dx,dy);
						not_visited-=1;
						move(dx, dy,maze);
					}
					if(dir==Direction::left)
					{
						//std::cout<<"VALID"<<std::endl;
						maze.removeWall(dy,dx,dir);
						visited(dx,dy);
						dy-=1;
						visited(dx,dy);
						//update_coor(x,y,dir);

						//visited(dx,dy);
						not_visited-=1;
						move(dx, dy,maze);
					}
					

				}

				if(no_moves(dx,dy))
					{
					//std::cout<<"no moves!"<<std::endl;
					return;
					}
				
					move(dx,dy,maze);
				//std::cout<<"not in bounds"<<std::endl;
		
			
	}
	void generateMaze(Maze& maze);
	/*
	{

		//Maze x_maze=maze.clone();
		_h=maze.getHeight();
		_w=maze.getWidth();
		_refresh(maze);
		
		//bool k=Direction::right==Direction::right;
		//std::cout<<k<<std::endl;
		//std::cin>>"start: ";
		std::cout<<"refresh complete"<<std::endl;
		new_vect(maze);
		std::cout<<"new vector created"<<std::endl;
	//while(not_visited!=0)
	//{
		move(0,0,maze);
		std::cout<<not_visited<<std::endl;
	//}
		
		std::cout<<"done!"<<std::endl;
		
		
		
		
	}
	*/
	

};






#endif // MYMAZEGENERATOR_HPP