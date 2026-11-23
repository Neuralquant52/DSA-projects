#include "kMeans.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <format>

int main(){
	std::srand(std::time({}));
	using Point = std::pair<int, int>;
	std::vector<Point> points;

	for (int i{}; i < 100; i++)
		points.emplace_back(Point{std::rand() % 100, std::rand() % 100});

	Cluster cluster(points);
	cluster.generateClusters(10);

	auto clusters = cluster.getClusters();

	for (const auto& [c, points] : clusters){
		std::cout << std::format("Cluster ({}, {}) : \n", c.first, c.second);
		for (const auto& p : points){
			std::cout << std::format("Point : {}, {}\n", p.first, p.second);
		}

		std::cout << "---------------------------\n";
	}	

	return 0;
}
