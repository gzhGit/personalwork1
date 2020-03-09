#include "pch.h"
#include "CppUnitTest.h"
#include "../lineCrossover/main.h" 
#include <vector>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			/*Line* line1 = new Line(0, 0, 1, 1);
			Line* line2 = new Line(1, 0, 1, 1);
			Line* line3 = new Line(0, 0, -1, -1);
			Line* line4 = new Line(0, 1, 1, 0);
			Node node1 = line1->calCrossover(*line2);
			Node node2 = line3->calCrossover(*line4);
			Assert::AreEqual(node1.x, 1.0);
			Assert::AreEqual(node1.y, 1.0);
			Assert::AreEqual(node2.x, 0.5);
			Assert::AreEqual(node2.y, 0.5);*/
			Line* line1 = new Line(0, 0, 1, 1);
			Line* line2 = new Line(2, 0, 2, -1123);
			Circle* circle1 = new Circle(2, 2, 1);
			Circle* circle2 = new Circle(0, 0, 3);
			Circle* circle3 = new Circle(0, 0, 2);
			Circle* circle4 = new Circle(10, 0, 1);
			Object o1(0, line1);
			Object o2(1, circle1);
			Object o3(1, circle2);
			Intersect i;
			vector<Node> v1 = i.circleCrossCircle(*(o2.circle), *(o3.circle));
			vector<Node> v2 = i.lineCrossCircle(*(o1.line), *(o2.circle));
			vector<Node> v3 = i.lineCrossLine(*line1, *line2);
			vector<Node> v4 = i.lineCrossCircle(*line2, *circle2);
			vector<Node> v5 = i.lineCrossCircle(*line2, *circle3);
			vector<Node> v6 = i.lineCrossCircle(*line1, *circle4);
			int size1 = v1.size();
			int size2 = v2.size();
			/*cout << v1.at(0).x << endl;
			cout << v1.at(1).y << endl;
			cout << v2.at(0).x << endl;
			cout << v2.at(1).y << endl;*/
			Assert::AreEqual(size1, 2);
			Assert::AreEqual(size2, 2);
			Assert::AreEqual((int)v3.size(), 1);
			Assert::AreEqual((int)v4.size(), 2);
			Assert::AreEqual((int)v5.size(), 1);
			Assert::AreEqual((int)v6.at(0).judgeCross, 0);
		}
	};
}
