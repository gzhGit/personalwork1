#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "main.h"
#include <math.h>
#include <set>
using namespace std;

Line::Line() {};

Line::Line(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	//cal paras:k b x special
	if (x1 == x2) {
		this->special = 1;
		this->x = (double)x1;
	}
	else {
		this->special = 0;
		this->k = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
		this->b = (double)y1 - k * (double)x1;
	}

}

Line::Line(double x) {
	this->special = 1;
	this->x = x;
}

Line::Line(double k, double b) {
	this->special = 0;
	this->k = k;
	this->b = b;
}

/*Node Line::calCrossover(Line line) {
	if (this->special == 1) {
		if (line.special == 1) {
			Node node(0);
			return node;
		}
		else {
			double x = this->x;
			double y = line.k*x + line.b;
			Node node(1, x, y);
			return node;
		}
	}

	else {
		if (line.special == 1) {
			double x = line.x;
			double y = this->k*x + this->b;
			Node node(1, x, y);
			return node;
		}
		else if (line.k == this->k) {
			Node node(0);
			return node;
		}
		else {
			double x = (line.b - this->b) / (this->k - line.k);
			double y = line.k*x + line.b;
			Node node(1, x, y);
			return node;
		}
	}
}*/

bool Node::operator<(const Node node) const {
	if (this->x < node.x) {
		return true;
	}
	else if (this->x == node.x) {
		if (this->y < node.y) {
			return true;
		}
	}
	return false;
}

Node::Node(int judgeCross) {
	this->judgeCross = judgeCross;
}

Node::Node(int judgeCross, double x, double y) {
	this->judgeCross = judgeCross;
	this->x = x;
	this->y = y;
}

Circle::Circle(int a, int b, int r) {
	this->a = a;
	this->b = b;
	this->r = r;
}

Object::Object() {
	this->line = new Line(0, 0, 0, 0);
	this->circle = new Circle(0, 0, 0);
};

Object::Object(int lineOrCircle, Line *line) {
	this->line = new Line(0, 0, 0, 0);
	this->circle = new Circle(0, 0, 0);
	this->lineOrCircle = lineOrCircle;
	*(this->line) = *line;
}

Object::Object(int lineOrCircle, Circle *circle) {
	this->line = new Line(0, 0, 0, 0);
	this->circle = new Circle(0, 0, 0);
	this->lineOrCircle = lineOrCircle;
	*(this->circle) = *circle;
}

vector<Node> Intersect::lineCrossLine(Line line1, Line line2) {
	vector<Node> result;
	if (line1.special == 1) {
		if (line2.special == 1) {
			Node node(0);
			result.push_back(node);
			return result;
		}
		else {
			double x = line1.x;
			double y = line2.k*x + line2.b;
			Node node(1, x, y);
			result.push_back(node);
			return result;
		}
	}

	else {
		if (line2.special == 1) {
			double x = line2.x;
			double y = line1.k*x + line1.b;
			Node node(1, x, y);
			result.push_back(node);
			return result;
		}
		else if (line2.k == line1.k) {
			Node node(0);
			result.push_back(node);
			return result;
		}
		else {
			double x = (line2.b - line1.b) / (line1.k - line2.k);
			double y = line2.k*x + line2.b;
			Node node(1, x, y);
			result.push_back(node);
			return result;
		}
	}
}

vector<Node> Intersect::lineCrossCircle(Line line, Circle circle) {
	vector<Node> result;
	if (line.special == 1) {
		if (abs(line.x - circle.a) > circle.r) {
			Node node(0);
			result.push_back(node);
			return result;
		}
		else if (abs(line.x - circle.a) == circle.r) {
			Node node(1, line.x, circle.b);
			result.push_back(node);
			return result;
		}
		else {
			//cout << "straight line cross cir!" << endl;
			double s = sqrt((double)circle.r*circle.r - (double)(line.x - circle.a)*(line.x - circle.a));
			Node node1(1, line.x, circle.b + s);
			Node node2(1, line.x, circle.b - s);
			result.push_back(node1);
			result.push_back(node2);
			return result;
		}
	}
	else {
		double k = line.k;
		int a = circle.a;
		int b = circle.b;
		double c = line.b;
		int r = circle.r;
		double distance = abs(k*a - b + c) / sqrt(1 + k * k);
		if (distance > r) {
			Node node(0);
			result.push_back(node);
			return result;
		}
		else if (distance == r) {
			double x_ = (a + b * k - c * k) / (1 + k * k);
			double y_ = k * x_ + c;
			Node node(1, x_, y_);
			result.push_back(node);
			return result;
		}
		else {
			//cout << "normal line cross cir" << endl;
			double temp1 = a + b * k - c * k;
			double temp2 = 1 + k * k;
			double temp3 = (double)r * r - (double)a * a - (c - b)*(c - b);
			double s = sqrt(temp1 * temp1 + temp2 * temp3);
			double x_1 = (temp1 + s) / temp2;
			double y_1 = k * x_1 + c;
			double x_2 = (temp1 - s) / temp2;
			double y_2 = k * x_2 + c;
			Node node1(1, x_1, y_1);
			Node node2(1, x_2, y_2);
			result.push_back(node1);
			result.push_back(node2);
			return result;
		}
	}
}

vector<Node> Intersect::circleCrossCircle(Circle c1, Circle c2) {
	vector<Node> result;
	int a1 = c1.a;
	int b1 = c1.b;
	int r1 = c1.r;
	int a2 = c2.a;
	int b2 = c2.b;
	int r2 = c2.r;
	double distance = sqrt((a1 - a2)*(a1 - a2) + (b1 - b2)*(b1 - b2));
	int r = r1 + r2;
	if (distance > r) {
		//cout << "no intersects cir by cir" << endl;
		Node node(0);
		result.push_back(node);
		return result;
	}
	else if (distance == r) {
		//cout << "only one cir by cir!" << endl;
		Line through = Line(a1, b1, a2, b2);
		vector<Node> temp = lineCrossCircle(through, c1);
		int i = 0;
		for (; i < 2; i++) {
			Node node = temp.at(i);

			int judge_node_x = (((node.x > (double)a1) && (node.x < (double)a2)) ||
				((node.x > (double)a2) && (node.x < (double)a1)));
			int judge_node_x_special = (node.x == (double)a1) && (node.x == (double)a2);

			int judge_node_y = (((node.y > (double)b1) && (node.x < (double)b2)) ||
				((node.y > (double)b2) && (node.x < (double)b1)));
			int judge_node_y_special = (node.y == (double)b1) && (node.y == (double)b2);
		
			if ((judge_node_x || judge_node_x_special) &&
				(judge_node_y || judge_node_y_special)) {
				result.push_back(node);
				break;
			}
		}
		return result;
	}
	//
	else if ((distance < r) && (distance > abs(r1-r2))){
		//cout << "two cir by cir!" << endl;
		int d1 = -a1 * 2;
		int d2 = -a2 * 2;
		int e1 = -b1 * 2;
		int e2 = -b2 * 2;
		int f1 = a1 * a1 + b1 * b1 - r1 * r1;
		int f2 = a2 * a2 + b2 * b2 - r2 * r2;
		int special = 0;
		Line shared = Line();
		if (e1 == e2) {
			special = 1;
			double x = ((double)f2 - (double)f1) / ((double)d1 - (double)d2);
			/*cout << "f1:" << f1 << endl;
			cout << "f2:" << f2 << endl;
			cout << "d1:" << d1 << endl;
			cout << "d2:" << d2 << endl; */
			shared = Line(x);
		}
		else {
			double k = ((double)d2 - (double)d1) / ((double)e1 - (double)e2);
			double b = ((double)f2 - (double)f1) / ((double)e1 - (double)e2);
			shared = Line(k, b);
		}
		vector<Node> result = lineCrossCircle(shared, c1);
		return result;
	}
	else if (distance == abs(r1 - r2)) {
		Line through = Line(a1, b1, a2, b2);
		vector<Node> temp1 = lineCrossCircle(through, c1);
		vector<Node> temp2 = lineCrossCircle(through, c2);
		int i,j;
		int judge = 0;
		for (i = 0; i < 2; i++) {
			Node node1 = temp1.at(i);
			for (j = 0; j < 2; j++) {
				Node node2 = temp2.at(j);
				if ((abs(node1.x-node2.x) < 0.00000001) && (abs(node1.y - node2.y) < 0.00000001)) {
					result.push_back(node1);
					judge = 1;
					break;
				}	
			}
			if (judge == 1) {
				break;
			}
		}
		return result;
	}
	else {
		Node node = Node(0);
		result.push_back(node);
		return result;
	}
}

//warning C4172
int renum[4];

int* string2num(char inputstring[],int kind) {
	renum[0] = renum[1] = renum[2] = renum[3];
	int i=2,len=0,count;
	char temp[4][1024];
	for (count = 0; count < kind; count++) {
		len = 0;
		while (1) {
			if (inputstring[i] == ' ' || inputstring[i] == '\t') {
				break;
			}
			temp[count][len] = inputstring[i];
			len++;
			i++;
			if (i == strlen(inputstring)) {
				break;
			}
		}
		if (inputstring[i] == ' ' || inputstring[i] == '\t') {
			i++;
		}
		else if (i == strlen(inputstring)) {
			break;
		}
	}
	for (count = 0; count < kind; count++) {
		renum[count] = atoi(temp[count]);
	}
	return renum;
}

int main(int argc, char **argv) {
	char input[1024],output[1024];
	
	//get input&output file name
	if (argc == 5) {
		if (strcmp(argv[1], "-i") == 0) {
			strcpy(input, argv[2]);
			if (strcmp(argv[3], "-o") == 0) {
				strcpy(output, argv[4]);
			}
		}
		else if (strcmp(argv[1], "-o") == 0) {
			strcpy(output, argv[2]);
			if (strcmp(argv[3], "-i") == 0) {
				strcpy(input, argv[4]);
			}
		}
	} 
	//else return 1;
	//	strcpy(input, "../Debug/input6.txt");
	//	strcpy(output, "../Debug/output6.txt");
	char inputstring[1024];
	char firstnum[1024];
	int numOfLines;
	
	ifstream inputFile;
	ofstream outputFile;
	
	//vector<Line>* lineVector = new vector<Line>();
	vector<Object>* objVector = new vector<Object>();
	vector<Node>* nodeVector = new vector<Node>();
	set<Node>* nodeSet = new set<Node>();

	inputFile.open(input,ios::in);
	outputFile.open(output, ios::out);
	
	inputFile.getline(firstnum,1024);
	//cout << firstnum << endl;
	numOfLines = atoi(firstnum);
	
	//calculate
	int countLines,*xy;
	char cOrL = ' ';
	for (countLines = 0; countLines < numOfLines; countLines++) {
		inputFile.getline(inputstring, 1024);
		//cout << inputstring << endl;
		Object obj;
		if (inputstring[0] == 'L') {
			xy = string2num(inputstring,4);
			int x1 = *xy;
			int y1 = *(xy + 1);
			int x2 = *(xy + 2);
			int y2 = *(xy + 3);
			Line *line = new Line(x1, y1, x2, y2);
			obj = Object(0, line);
		}
		else if (inputstring[0] == 'C') {
			xy = string2num(inputstring,3);
			int a = *xy;
			int b = *(xy + 1);
			int r = *(xy + 2);
			Circle *circle = new Circle(a, b, r);
			obj = Object(1, circle);
		}
		objVector->push_back(obj);
		//lineVector->push_back(line);
		if (countLines != 0) {
			int count = 0;
			for (count = 0; count < countLines; count++) {
				Object objCross = objVector->at(count);
				vector<Node> result;
				Intersect cal;
				if (obj.lineOrCircle == 0) {
					if (objCross.lineOrCircle == 0) {
						result = cal.lineCrossLine(*(obj.line), *(objCross.line));
					}
					else if (objCross.lineOrCircle == 1) {
						result = cal.lineCrossCircle(*(obj.line), *(objCross.circle));
					}
				}
				else if (obj.lineOrCircle == 1) {
					if (objCross.lineOrCircle == 0) {
						result = cal.lineCrossCircle(*(objCross.line), *(obj.circle));
					}
					else if (objCross.lineOrCircle == 1) {
						//cout << "circleCrossCircle!" << endl;
						result = cal.circleCrossCircle(*(obj.circle), *(objCross.circle));
					}
				}
				
				int runover;
				for (runover = 0; runover < (int)result.size(); runover++) {
					Node node = result.at(runover);
					if (node.judgeCross == 1) {
					/*	vector<Node>::iterator it;
						int judge = 0;
						for (it = nodeVector->begin(); it != nodeVector->end(); it++) {
							if ((it->x == node.x) && (it->y == node.y)) {
								judge = 1;
								break;
							}
						}
						if (judge == 0) {
							cout << "x:" << node.x << endl;
							cout << "y:" << node.y << endl;
							nodeVector->push_back(node);
						} */
						nodeSet->insert(node);
					}
				}
			
			}
		}
	}

	//cout << "all nodes:" << endl;
	/*set<Node>::iterator it;
	for (it = nodeSet->begin(); it != nodeSet->end(); it++) {
		cout << "x:" << it->x << "	";
		cout << "y:" << it->y << endl;
	}*/
	//int result = nodeVector->size();
	int result = nodeSet->size();
	outputFile << result << endl;

	return 0;
}