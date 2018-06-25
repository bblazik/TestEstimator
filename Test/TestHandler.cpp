#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tester/HistoricDataHandler.hpp"
#include "../Tester/CsvDataHandler.h"
#include <fstream>
#include <functional>
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace
{
constexpr char sampleBuffer[] = "1,2\n"
								"1,3\n"
								"4,5\n"
								"2,3\n"
								"1,10\0";
constexpr char incorectSeparatorBuffer[] =  "1;2\n"
											"1;3\n"
											"4;5\n"
											"2;3\n"
											"1;10\0";
constexpr char invalidPath[] = "ivalid path";
constexpr auto expectedSize = 5u;
}

TEST_CLASS(TestCsvDataHandler)
{
public:

	TEST_METHOD(whenDataAquairedThenSizeIsAsExpected)
	{
		auto& stream = std::istringstream(sampleBuffer);
		createStream(stream);

		const auto data = csv->getData();
		Assert::AreEqual(data.size(), expectedSize);
	}

	TEST_METHOD(whenDataAquairedThenDataCanBeAcuairedAnotherTime) 
	{
		auto& stream = std::istringstream(sampleBuffer);
		createStream(stream);

		const auto data = csv->getData();
		const auto data2 = csv->getData();

		Assert::AreEqual(data.size(), data2.size());
	}
	
	TEST_METHOD(whenDataAquairedThenFirstElemIsAsExpected)
	{
		auto& stream = std::istringstream(sampleBuffer);
		createStream(stream);

		const auto firstElem = dataStructures::Test{ 1u, 2.0f };
		const auto lastElem = dataStructures::Test{ 1u, 10.0f };
		const auto data = csv->getData();

		Assert::IsTrue(data.front() == firstElem); //Assert::AreSame return some vs studio error #10626
		Assert::IsTrue(data.back() == lastElem); 
	};
	
	TEST_METHOD(whenInvalidThenDataNotAquiredGivenException)
	{
		auto& stream = std::ifstream(invalidPath);
		createStream(stream);

		auto f1 = [this] { return csv->getData(); };
		Assert::ExpectException<std::istream::failure>(f1);
	}

	TEST_METHOD(whenDataHasIncorrectSeparatorsThenDontHandle) 
	{		
		auto& sstream = std::istringstream(incorectSeparatorBuffer);
		createStream(sstream);
		Assert::AreNotEqual(csv->getData().size(), expectedSize);		
	}
	
	void createStream(std::istream& stream)
	{		
		csv = std::make_unique<CsvDataHandler>(stream);
	}

private:
	std::unique_ptr<HistoricDataHandler> csv;
};