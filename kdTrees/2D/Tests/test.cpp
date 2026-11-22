#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "../2D.hpp"


using Point = std::pair<int, int>;

TEST(two_d, closest){
	std::vector<Point> points = {{2,3}, {3,6}, {4,5}, {5,2}, {6,4}, {7,5}};
	ClosestNeighbor tester(points);
	
	EXPECT_EQ(tester.closestTo({3, 6}), Point(3, 6));
	EXPECT_EQ(tester.closestTo({4, 3}), Point(5, 2));
	EXPECT_EQ(tester.closestTo({1, 6}), Point(3, 6));
	EXPECT_EQ(tester.closestTo({5, 5}), Point(4, 5));
	EXPECT_EQ(tester.closestTo({6, 3}), Point(6, 4));
	EXPECT_EQ(tester.closestTo({100, 100}), Point(7, 5));
	EXPECT_EQ(tester.closestTo({-10, -10}), Point(2, 3));
}


int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
