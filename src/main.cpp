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
		
		Line(int x1,int y1,int x2,int y2);
		Node calCrossover(Line line);
};

Line::Line(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;

	//cal paras:k b x special
	if (x1 == x2) {
		this->special = 1;
		this->x = x1;
	}
	else {
		this->special = 0;
		this->k = (y2 - y1) / (x2 - x1);
		this->b = y1 - k * x1;
	}

}

Node Line::calCrossover(Line line) {
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
}

Node::Node(int judgeCross) {
	this->judgeCross = judgeCross;
}

Node::Node(int judgeCross, double x, double y) {
	this->judgeCross = judgeCross;
	this->x = x;
	this->y = y;
}

int* string4num(char inputstring[]) {
	int renum[4];
	int i=2,len=0,count;
	char temp[4][2024];
	for (count = 0; count < 4; count++) {
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
	for (count = 0; count < 4; count++) {
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
	else return 1;

	char inputstring[1024];
	char firstnum[1024];
	int numOfLines;
	
	ifstream inputFile;
	ofstream outputFile;
	
	vector<Line>* lineVector = new vector<Line>();
	vector<Node>* nodeVector = new vector<Node>();

	inputFile.open(input,ios::in);
	outputFile.open(output, ios::out);
	
	inputFile.getline(firstnum,1024);
	cout << firstnum << endl;
	numOfLines = atoi(firstnum);
	
	//calculate
	int countLines,*xy4;
	for (countLines = 0; countLines < numOfLines; countLines++) {
		inputFile.getline(inputstring, 1024);
		cout << inputstring << endl;
		xy4 = string4num(inputstring);
		int x1 = *xy4;
		int y1 = *(xy4 + 1);
		int x2 = *(xy4 + 2);
		int y2 = *(xy4 + 3);
		Line line(x1, y1, x2, y2);
		lineVector->push_back(line);
		if (countLines != 0) {
			int count = 0;
			for (count = 0; count < countLines; count++) {
				Line line1 = lineVector->at(count);
				Node node = line.calCrossover(line1);
				if (node.judgeCross == 1) {
					vector<Node>::iterator it;
					int judge = 0;
					for (it = nodeVector->begin(); it != nodeVector->end(); it++) {
						if ((it->x == node.x) && (it->y == node.y)) {
							judge = 1;
							break;
						}
					}
					if (judge == 0) {
						nodeVector->push_back(node);
					}
				}
			}
		}
	}
	
	int result = nodeVector->size();

	outputFile << result << endl;

	return 0;
}