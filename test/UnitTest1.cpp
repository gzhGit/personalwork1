#include "pch.h"
#include "CppUnitTest.h"
#include "../lineCrossover/main.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Line* line1 = new Line(0, 0, 1, 1);
			Line* line2 = new Line(1, 0, 1, 1);
			Line* line3 = new Line(0, 0, -1, -1);
			Line* line4 = new Line(0, 1, 1, 0);
			Node node1 = line1->calCrossover(*line2);
			Node node2 = line3->calCrossover(*line4);
			Assert::AreEqual(node1.x, 1.0);
			Assert::AreEqual(node1.y, 1.0);
			Assert::AreEqual(node2.x, 0.5);
			Assert::AreEqual(node2.y, 0.5);
		}
	};
}
