#include "CppUnitTest.h"
#include "Color.h"
#include "ByteManipulation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GingerbreadChipTests
{
	TEST_CLASS(ByteManipulationTests)
	{
	public:

		TEST_METHOD(TestTruncateUnsignedIntToByte)
		{
			Assert::AreEqual<unsigned char>(0u, ByteManipulation::TruncateToByte(0u));
			Assert::AreEqual<unsigned char>(1u, ByteManipulation::TruncateToByte(1u));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(255u));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(256u));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(1234567u));
		}

		TEST_METHOD(TestTruncateSignedIntToByte)
		{
			Assert::AreEqual<unsigned char>(0u, ByteManipulation::TruncateToByte(-1));
			Assert::AreEqual<unsigned char>(0u, ByteManipulation::TruncateToByte(0));
			Assert::AreEqual<unsigned char>(1u, ByteManipulation::TruncateToByte(1));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(255));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(256));
			Assert::AreEqual<unsigned char>(255u, ByteManipulation::TruncateToByte(1234567));
		}
	};
}
