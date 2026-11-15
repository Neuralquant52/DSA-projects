#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <ostream>
#include <queue>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <utility>
#include <vector>
#include <set>


class MazeSolver {
public:
	std::string render(char c){
	    switch (c){
		case '#': return "\033[38;5;240m██\033[0m";
		case ' ': return "  ";                     
		case 'E': return "\033[31m⌂ \033[0m";        
		case 'O': return "\033[32m░░\033[0m";        
		case 'o': return "\033[36m░░\33[0m";     
		case 'S': return "\033[35m◉ \033[0m";    
		default:  return "??";
	    }
	}

	MazeSolver(std::vector<std::vector<char>> maze_, std::pair<int, int> begin_) : maze(maze_), begin(begin_) {}
	
	void printMaze(){
		for (int x{}; x < maze.size(); x++){
			for (int y{}; y < maze.front().size(); y++){
				std::cout << render(maze[x][y]);
			}
			std::cout << '\n';
		}
		std::cout << "\033[" << maze.size() << "A" << std::flush;
	}

	void bfs(){
		std::queue<std::pair<int, int>> q; 
		int rows = maze.size(), columns = maze.front().size();
		q.push(begin);
		visits.insert(begin);
		std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(columns, {-1, -1}));
		std::vector<std::pair<int, int>> neighbors = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

		while (!q.empty()){
			int sz = q.size();
			for (int i{}; i < sz; i++){
				auto [r, c] = q.front(); q.pop();
				if (maze[r][c] == 'E'){
					auto curr = parent[r][c];
					while (curr != begin){
						maze[curr.first][curr.second] = 'O';
						curr = parent[curr.first][curr.second];
					}
					printMaze();
					return;
				}

				for (auto [dr, dc] : neighbors){
				    int nr = r + dr, nc = c + dc;

				    if (nr < 0 || nc < 0 || nr >= rows || nc >= columns ||
					visits.contains({nr, nc}) || maze[nr][nc] == '#') continue;

				    visits.insert({nr, nc});
				    parent[nr][nc] = {r, c};
				    if (maze[nr][nc] != 'E') maze[nr][nc] = 'o';
				    q.push({nr, nc});
				}
				printMaze();
				std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
			}
		}	
	}

	bool dfs(int r, int c){
		int rows = maze.size(), columns = maze.front().size();

		if (std::min(r, c) < 0 ||
		r == rows || c == columns ||
		visits.contains({r, c}) || maze[r][c] == '#') return false;
		
		if (maze[r][c] == 'E') return true;

		visits.insert({r, c});
		maze[r][c] = 'o';
		printMaze();
		
		if(dfs(r+1, c)) return true;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / 3));
		if (dfs(r-1, c)) return true;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / 3));
		if (dfs(r, c+1)) return true;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time / 3));
		if (dfs(r, c-1)) return true;
		
		return false;
	}
	
private:
	int sleep_time = 30;
	std::set<std::pair<int, int>> visits;
	std::vector<std::vector<char>> maze;
	std::pair<int, int> begin;
};

