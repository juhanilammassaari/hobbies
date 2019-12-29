#include "CppUnitTest.h"
#include "Color.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GingerbreadChipTests
{
	TEST_CLASS(ColorTests)
	{
	public:
		
		TEST_METHOD(TestInitialState)
		{
			Color color;
			Assert::AreEqual<unsigned char>(0, color.GetRed());
			Assert::AreEqual<unsigned char>(0, color.GetGreen());
			Assert::AreEqual<unsigned char>(0, color.GetBlue());
		}
	};
}
