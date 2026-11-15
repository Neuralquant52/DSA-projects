#include <cstdlib>
#include "MazeSolver.hpp"

int main(){
	int rows = 25;
	int cols = 40;


std::vector<std::vector<char>> maze(rows, std::vector<char>(cols));

	for (int x{}; x < rows ; x++){
		for (int y{}; y < cols ; y++){
			if (x == 0 || x == rows-1 || y == 0 || y == cols-1) maze[x][y] = '#';
			else maze[x][y] = std::rand() % 100 < 30 ? '#' : ' ';
		}
	}
	
	maze[rows-2][cols-2] = 'E';

	MazeSolver solver(maze, {1, 1});

	solver.printMaze();
	std::cout << "\033[" << rows << "B" << std::flush; 
}
