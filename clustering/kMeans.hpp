#include <algorithm>
#include <cmath>
#include <memory>
#include "features/2D.hpp"
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>
#include <vector>
#include <span>
#include <cstddef>

class Cluster {
	using Point = std::pair<int, int>;
	using Centroid = std::pair<double, double>;
public:
	Cluster(std::span<Point> points){
		std::srand(std::time({}));
		for (Point& p : points){
			points_.emplace_back(std::move(p));
			if (p > max_)
			   max_ = p;
		}
	}
	
	void generateClusters(int numCentroids){	
		for (int i{}; i < numCentroids; i++){
			auto centroid = Centroid{std::rand() % max_.first, std::rand() % max_.second};
			centroids_.emplace_back(centroid);
		}
				
		kdTree = std::make_unique<ClosestNeighbor>(centroids_);
		
		for (const auto& p : points_){
			Point closest = kdTree->closestTo(p);
			clusters_.emplace_back(p, closest);
		}
		
		std::vector<double> distances = updateClusters();
		
		while (std::any_of(distances.begin(), distances.end(), [](double x){return x > 0.6;})){	
			distances = updateClusters();
		};
	}
	
	double computeInertia(){
		double inertia = 0;

		for (const auto& [p, c] : clusters_){
			inertia += std::pow(calcDistance(p, c), 2);
		}
		return inertia;
	}

	std::vector<std::pair<Centroid, std::vector<Point>>> getClusters(){
		std::vector<std::pair<Centroid, std::vector<Point>>> res;
		std::map<Centroid, std::vector<Point>> adj;
		
		for (auto& centroid : centroids_){
			adj[centroid] = std::vector<Point>();
		}

		for (auto& [p, c] : clusters_){
			adj[c].emplace_back(p);
		}

		for (auto it : adj){
			res.emplace_back(it);
		}	

		return res;
	}
private:

	std::vector<double> updateClusters(){
		std::map<Centroid, std::vector<Point>> adj;
		std::map<Centroid, Centroid> oldToNew;	
		std::vector<Centroid> newCentroids;
		std::vector<double> distances;

		for (auto& c : centroids_)
			adj[c] = std::vector<Point>();

		for (auto& [p, centroid] : clusters_){
			adj[centroid].emplace_back(p);	
		}

		for (auto& [c, points] : adj){
			Centroid old = c;
			
			Centroid updated = points.empty() ? c : calcMean(adj[c]);
			
			oldToNew[old] = updated;
			distances.push_back(calcDistance(old, updated));
			newCentroids.emplace_back(updated);
		}


		kdTree = std::make_unique<ClosestNeighbor>(newCentroids);
		centroids_ = std::move(newCentroids);

		for (auto& [p, c] : clusters_){
			c = kdTree->closestTo(p);
		}


		return distances;
	}


	Centroid calcMean(std::span<Point> points){
		if (points.empty())
			return Point{0, 0};
	
		std::size_t sz = points.size();
		double xSum{}, ySum{};

		for (const auto& [x, y] : points){
			xSum += x;
			ySum += y;
		}
		return std::make_pair(xSum / sz, ySum / sz);
	}

   	double calcDistance(const std::pair<double, double>& a, const std::pair<double, double>& b){
                    return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
    	}

	Point max_;
	std::unique_ptr<ClosestNeighbor> kdTree;
	
	std::vector<Point> points_;
	std::vector<Centroid> centroids_;
	std::vector<std::pair<Point, Centroid>> clusters_;
};
