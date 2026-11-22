#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>
#include <vector>
#include "../bst.hpp"

class ClosestNeighbor {
	using Point = std::pair<int, int>;
public:
	ClosestNeighbor(std::vector<Point> points){
		int avgX = 0, avgY = 0;
		for (const auto& [x, y] : points){
			avgX += x;
			avgY += y;
		}		
		
		avgX /= points.size();
		avgY /= points.size();

		Point avgPoint = std::make_pair(avgX, avgY);

		std::sort(points.begin(), points.end(), [&](Point& a, Point& b){
			return calcDistance(avgPoint, a) < calcDistance(avgPoint, b);		
		});
		
		for (auto& p : points){
			Tree.insert(p);
		}
	}

	Point closestTo(Point point){
		auto curr = Tree.data();
		if (!curr)
			throw std::logic_error("List of neighbors empty");


		Point best = curr->key;
		double bestDistance = calcDistance(point, best);
		
		search(curr, point, best, bestDistance);
		return best;
	}

private:
	void search(auto* n, Point& target, Point& best, double& bestDistance){
		if (!n)
		   return;

		double distance = calcDistance(target, n->key);
		if (distance < bestDistance){
			bestDistance = distance;
			best = n->key;
		}

		bool goLeft = target < n->key;
		auto* nearSide = goLeft ? n->left : n->right;
		auto* farSide = goLeft ? n->right : n->left;

		search(nearSide, target, best, bestDistance);

		double dx = n->key.first - target.first;
		if (std::abs(dx) < bestDistance)
			search(farSide, target, best, bestDistance);

	}

	BST<Point> Tree;

	double calcDistance(Point& a, Point& b){
		return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
	}
};
