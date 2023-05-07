#include "pch.h"
#include "Node.h"
#include "Node.cpp"
#include "Edge.h"
#include "Edge.cpp"
#include "MYAlgorithm.h"
#include "Algorithm.cpp"


TEST(NodeTest, TestClassFunc) {
	Node a;
	Node b(1, 2, 3);
	EXPECT_EQ(0, a.GetY());
	EXPECT_EQ(0, a.GetID());
	EXPECT_EQ(0, a.GetX());
	EXPECT_EQ(0, a.GetY());
	EXPECT_EQ(0, a.GetID());
	EXPECT_EQ(1, b.GetX());
	EXPECT_EQ(2, b.GetY());
	EXPECT_EQ(3, b.GetID());
	a = b;
	EXPECT_EQ(true, b == a);
	EXPECT_EQ(b.GetX(), a.GetX());
	EXPECT_EQ(b.GetY(), a.GetY());
	EXPECT_EQ(b.GetID(), a.GetID());

}
TEST(EdgeTest, TestClassFunc) {
	Node node1(1, 2, 3), node2;
	Edge edge1;
	Edge edge2(node1, node2);

	EXPECT_EQ(0, edge1.GetNode1().GetX());
	EXPECT_EQ(0, edge1.GetNode1().GetY());
	EXPECT_EQ(0, edge1.GetNode1().GetID());
	EXPECT_EQ(1, edge2.GetNode1().GetX());
	EXPECT_EQ(2, edge2.GetNode1().GetY());
	EXPECT_EQ(3, edge2.GetNode1().GetID());

	EXPECT_TRUE(edge2.GetNode1() == node1);
}
TEST(AlgorithmTest, TestFunc) {
	Node node1(2, 2, 2), node2(0, 0, 0);
	Node node3(0, 2, 3), node4(2, 0, 4);
	Node a(-1, 3, 4), b(-1, 2, 5);
	Edge edge1(node3, node4);
	Edge edge2(node1, node2);
	Edge edge3(a, b);
	Edge edge4(a, node1);
	EXPECT_TRUE(intersect(node1, node2, node3, node4));
	EXPECT_FALSE(intersect(node1, node2, a, b));

	EXPECT_TRUE(IsIntersect(edge1, edge2));
	EXPECT_TRUE(IsIntersect(edge2, edge1));
	EXPECT_FALSE(IsIntersect(edge3, edge1));
	EXPECT_FALSE(IsIntersect(edge1, edge3));
	EXPECT_FALSE(IsIntersect(edge3, edge2));
	Node newnode(1, 1, 2);
	EXPECT_EQ(1, on_segment(newnode, node2, node1));
	EXPECT_EQ(1, on_segment(newnode, node1, node2));
	EXPECT_EQ(0, on_segment(newnode, node1, node3));

	EdgeArray.push_back(edge1);
	EdgeArray.push_back(edge2);
	EdgeArray.push_back(edge3);
	EdgeArray.push_back(edge4);
	Node c(1, 1, 0), f(5, 5, 2);
	Node d(-1, 0, 7), e(1, 8, 2), g(-10, 3, 9);
	Edge edge5(d, e), edge6(d, g);
	EXPECT_TRUE(IsNodeInEdgeArray(c));
	EXPECT_FALSE(IsNodeInEdgeArray(f));
	EXPECT_TRUE(IsEdgeIntersectedEdgeArray(edge5));
	EXPECT_FALSE(IsEdgeIntersectedEdgeArray(edge6));
	EdgeArray.push_back(edge6);
	Node p(-4, 1, 0);
	EXPECT_TRUE(IsNodeInEdgeArray(p));
	//CreatNewNodeX_Y
	Node newNode(0, 0, 1);
	CreatNewNodeX_Y(newNode, node2, 36, 9);
	cout << newNode.GetX() << "  " << newNode.GetY() << endl;



}
