#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Node {
public:
	int judgeCross;
	double x, y;

	Node(int judgeCross);
	Node(int judgeCross, double x, double y);
};

class Line {
public:
	int x1, y1, x2, y2;
	int special;
	double k, b, x;

	Line(int x1, int y1, int x2, int y2);
	Node calCrossover(Line line);
};
