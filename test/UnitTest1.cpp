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
			Circle* circle1 = new Circle(2, 2, 1);
			Circle* circle2 = new Circle(0, 0, 3);
			Object o1(0, line1);
			Object o2(1, circle1);
			Object o3(1, circle2);
			Intersect i;
			vector<Node> v1 = i.circleCrossCircle(*(o2.circle), *(o3.circle));
			vector<Node> v2 = i.lineCrossCircle(*(o1.line), *(o2.circle));
			int size1 = v1.size();
			int size2 = v2.size();
			/*cout << v1.at(0).x << endl;
			cout << v1.at(1).y << endl;
			cout << v2.at(0).x << endl;
			cout << v2.at(1).y << endl;*/
			Assert::AreEqual(size1, 2);
			Assert::AreEqual(size2, 2);
			
		}
	};
}
