#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Tester/Evaluator.hpp"
#include "../Tester/SimpleEvaluator.h"
#include "MockHistoricDataHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	constexpr auto exampleId = 1u;
	constexpr auto expectedAverage = 38.5f;
	constexpr auto invalidId = 999u;
	constexpr auto expectedAverageInCaseOfInvalid = 0.0f;
	constexpr auto errorMargin = .001f;
	constexpr auto expectedAverage1 = 32.88f;
	constexpr auto expectedAverage2 = 35.27f;

	const auto twoIdData = DataContainer{ { 0, 10 },{ 1, 9 },{ 0, 47 },{ 0, 45 },{ 0, 43 },{ 1, 48 },{ 0, 54 },{ 1, 49 },{ 0, 38 },{ 0, 2 },{ 0, 7 },{ 0, 17 },{ 1, 30 },{ 1, 16 },{ 0, 34 },{ 1, 55 },{ 0, 39 },{ 1, 40 },{ 1, 30 },{ 1, 36 },{ 0, 24 },{ 0, 34 },{ 1, 8 },{ 1, 30 },{ 0, 40 },{ 0, 15 },{ 1, 25 },{ 1, 48 },{ 0, 13 },{ 1, 56 },{ 0, 28 },{ 1, 59 },{ 0, 47 },{ 1, 57 },{ 0, 43 },{ 1, 0 },{ 0, 0 },{ 1, 4 },{ 0, 21 },{ 1, 26 },{ 1, 31 },{ 0, 38 },{ 0, 36 },{ 0, 24 },{ 0, 8 },{ 1, 30 },{ 0, 39 },{ 1, 6 },{ 1, 50 },{ 1, 50 },{ 0, 19 },{ 0, 16 },{ 1, 20 },{ 0, 4 },{ 0, 19 },{ 1, 45 },{ 1, 23 },{ 0, 33 },{ 0, 34 },{ 0, 4 },{ 1, 25 },{ 1, 21 },{ 1, 29 },{ 0, 59 },{ 1, 53 },{ 1, 44 },{ 1, 1 },{ 1, 25 },{ 0, 41 },{ 0, 47 },{ 0, 40 },{ 1, 33 },{ 1, 34 },{ 0, 18 },{ 1, 54 },{ 1, 41 },{ 1, 54 },{ 0, 58 },{ 1, 27 },{ 0, 7 },{ 1, 59 },{ 1, 30 },{ 1, 50 },{ 0, 30 },{ 1, 7 },{ 1, 52 },{ 0, 4 },{ 1, 57 },{ 1, 35 },{ 1, 31 },{ 0, 11 },{ 1, 21 },{ 1, 4 },{ 1, 25 },{ 1, 12 },{ 0, 45 },{ 0, 25 },{ 1, 5 },{ 0, 42 },{ 1, 22 },{ 0, 25 },{ 0, 11 },{ 0, 3 },{ 0, 21 },{ 0, 1 },{ 1, 59 },{ 0, 48 },{ 1, 43 },{ 0, 27 },{ 0, 55 },{ 1, 21 },{ 0, 27 },{ 1, 48 },{ 1, 21 },{ 1, 12 },{ 0, 16 },{ 1, 29 },{ 0, 16 },{ 0, 49 },{ 1, 44 },{ 0, 10 },{ 1, 32 },{ 1, 30 },{ 0, 54 },{ 0, 5 },{ 0, 1 },{ 0, 27 },{ 0, 28 },{ 0, 19 },{ 0, 23 },{ 0, 0 },{ 0, 25 },{ 0, 59 },{ 0, 36 },{ 1, 21 },{ 0, 24 },{ 0, 4 },{ 0, 51 },{ 1, 10 },{ 1, 48 },{ 0, 29 },{ 0, 36 },{ 1, 16 },{ 0, 53 },{ 0, 32 },{ 0, 32 },{ 0, 24 },{ 0, 6 },{ 0, 0 },{ 0, 10 },{ 1, 2 },{ 1, 57 },{ 1, 19 },{ 1, 42 },{ 1, 44 },{ 0, 14 },{ 0, 37 },{ 0, 59 },{ 0, 35 },{ 0, 14 },{ 0, 56 },{ 1, 28 },{ 0, 10 },{ 0, 35 },{ 0, 54 },{ 0, 41 },{ 0, 38 },{ 0, 46 },{ 0, 11 },{ 0, 19 },{ 0, 53 },{ 0, 33 },{ 1, 2 },{ 1, 24 },{ 0, 42 },{ 1, 59 },{ 1, 59 },{ 0, 56 },{ 0, 22 },{ 1, 28 },{ 1, 57 },{ 1, 55 },{ 0, 31 },{ 0, 23 },{ 1, 54 },{ 0, 20 },{ 0, 51 },{ 1, 16 },{ 0, 7 },{ 1, 50 },{ 1, 31 },{ 1, 31 },{ 1, 12 },{ 1, 18 },{ 1, 16 },{ 1, 14 },{ 1, 54 },{ 0, 13 },{ 0, 18 },{ 1, 54 },{ 0, 56 },{ 0, 35 },{ 0, 1 },{ 0, 39 },{ 0, 24 },{ 0, 10 },{ 0, 54 },{ 0, 54 },{ 1, 8 },{ 0, 33 },{ 1, 6 },{ 1, 58 },{ 1, 35 },{ 0, 32 },{ 1, 58 },{ 0, 27 },{ 0, 3 },{ 0, 27 },{ 0, 59 },{ 1, 19 },{ 1, 46 },{ 1, 30 },{ 1, 19 },{ 0, 30 },{ 0, 15 },{ 0, 23 },{ 1, 38 },{ 1, 42 },{ 1, 40 },{ 1, 56 },{ 0, 57 },{ 0, 4 },{ 0, 48 },{ 0, 18 },{ 1, 52 },{ 0, 11 },{ 1, 58 },{ 1, 21 },{ 0, 12 },{ 1, 6 },{ 0, 5 },{ 1, 27 },{ 1, 43 },{ 0, 17 },{ 1, 29 },{ 1, 34 },{ 1, 31 },{ 1, 2 },{ 1, 44 },{ 0, 50 },{ 1, 37 },{ 1, 51 },{ 0, 25 },{ 1, 52 },{ 0, 53 },{ 1, 30 },{ 1, 23 },{ 0, 22 },{ 1, 43 },{ 1, 50 },{ 0, 34 },{ 0, 13 },{ 1, 20 },{ 0, 50 },{ 1, 6 },{ 1, 34 },{ 1, 47 },{ 0, 32 },{ 0, 21 },{ 1, 41 },{ 1, 54 },{ 0, 15 },{ 0, 53 },{ 0, 54 },{ 0, 8 },{ 1, 30 },{ 1, 1 },{ 1, 51 },{ 0, 12 },{ 1, 3 },{ 0, 47 },{ 1, 44 },{ 0, 50 },{ 1, 59 },{ 0, 2 },{ 1, 18 },{ 1, 54 },{ 1, 24 },{ 0, 37 },{ 0, 4 },{ 0, 20 },{ 1, 10 },{ 0, 51 },{ 0, 44 },{ 0, 16 },{ 1, 29 },{ 0, 44 },{ 1, 28 },{ 0, 51 },{ 0, 16 },{ 0, 57 },{ 1, 37 },{ 0, 25 },{ 1, 17 },{ 1, 2 },{ 1, 57 },{ 1, 6 },{ 1, 16 },{ 0, 44 },{ 1, 15 },{ 1, 39 },{ 0, 10 },{ 0, 55 },{ 1, 59 },{ 0, 11 },{ 1, 57 },{ 1, 45 },{ 1, 31 },{ 0, 44 },{ 0, 30 },{ 1, 42 },{ 1, 3 },{ 1, 53 },{ 1, 32 },{ 0, 33 },{ 0, 55 },{ 0, 16 },{ 0, 26 },{ 0, 36 },{ 1, 5 },{ 0, 59 },{ 1, 38 },{ 1, 48 },{ 0, 0 },{ 0, 15 },{ 1, 8 },{ 0, 30 },{ 0, 29 },{ 1, 38 },{ 1, 40 },{ 1, 49 },{ 0, 13 },{ 0, 27 },{ 1, 0 },{ 1, 12 },{ 1, 17 },{ 0, 27 },{ 0, 23 },{ 1, 56 },{ 1, 20 },{ 1, 21 },{ 0, 29 },{ 1, 4 },{ 0, 24 },{ 1, 19 },{ 0, 43 },{ 1, 5 },{ 1, 7 },{ 0, 45 },{ 1, 2 },{ 1, 59 },{ 1, 24 },{ 0, 24 },{ 1, 39 },{ 1, 9 },{ 0, 44 },{ 0, 3 },{ 1, 19 },{ 1, 22 },{ 0, 42 },{ 1, 25 },{ 1, 25 },{ 1, 7 },{ 1, 10 },{ 0, 48 },{ 0, 0 },{ 1, 54 },{ 1, 23 },{ 0, 26 },{ 0, 31 },{ 0, 29 },{ 0, 0 },{ 1, 49 },{ 1, 47 },{ 1, 16 },{ 0, 33 },{ 1, 3 },{ 1, 38 },{ 0, 53 },{ 1, 54 },{ 1, 5 },{ 1, 9 },{ 0, 12 },{ 1, 49 },{ 0, 13 },{ 0, 45 },{ 0, 25 },{ 0, 13 },{ 0, 6 },{ 1, 21 },{ 1, 7 },{ 0, 14 },{ 1, 52 },{ 0, 12 },{ 0, 56 },{ 1, 32 },{ 1, 44 },{ 1, 30 },{ 0, 18 },{ 1, 19 },{ 0, 2 },{ 1, 15 },{ 1, 27 },{ 0, 34 },{ 1, 24 },{ 1, 56 },{ 1, 9 },{ 1, 55 },{ 0, 54 },{ 0, 35 },{ 0, 21 },{ 0, 58 },{ 0, 55 },{ 1, 54 },{ 0, 34 },{ 1, 54 },{ 1, 17 },{ 0, 56 },{ 1, 21 },{ 0, 1 },{ 0, 51 },{ 0, 15 },{ 0, 56 },{ 0, 50 },{ 0, 46 },{ 1, 28 },{ 1, 13 },{ 1, 20 },{ 1, 1 },{ 1, 27 },{ 0, 14 },{ 1, 28 },{ 0, 53 },{ 0, 58 },{ 0, 8 },{ 1, 1 },{ 1, 11 },{ 1, 48 },{ 0, 58 },{ 1, 41 },{ 0, 5 },{ 0, 24 },{ 1, 41 },{ 1, 0 },{ 1, 32 },{ 0, 28 },{ 1, 32 },{ 0, 43 },{ 0, 14 },{ 1, 16 },{ 1, 39 },{ 1, 16 },{ 1, 42 },{ 0, 10 },{ 0, 9 },{ 1, 35 },{ 0, 51 },{ 0, 34 },{ 1, 12 },{ 1, 53 },{ 0, 2 },{ 0, 32 },{ 0, 58 },{ 1, 43 },{ 1, 26 },{ 1, 52 },{ 1, 32 },{ 0, 20 },{ 0, 23 },{ 1, 23 },{ 1, 5 },{ 0, 55 },{ 0, 20 },{ 1, 52 },{ 0, 1 },{ 1, 35 },{ 1, 58 },{ 0, 6 },{ 0, 2 },{ 0, 55 },{ 0, 9 },{ 0, 21 },{ 1, 11 },{ 1, 33 },{ 1, 39 },{ 1, 45 },{ 0, 38 },{ 0, 33 },{ 1, 13 },{ 0, 55 } };
	const auto defaultData = DataContainer{ { 19, 45 },{ 18, 21 },{ 41, 30 },{ 58, 19 },{ 18, 50 },{ 51, 59 },{ 4, 54 },{ 50, 6 },{ 45, 31 },{ 24, 26 },{ 6, 15 },{ 35, 20 },{ 3, 46 },{ 57, 29 },{ 16, 38 },{ 26, 18 },{ 50, 30 },{ 46, 7 },{ 46, 15 },{ 13, 46 },{ 32, 39 },{ 56, 40 },{ 58, 5 },{ 19, 27 },{ 33, 11 },{ 9, 13 },{ 20, 38 },{ 56, 51 },{ 16, 6 },{ 6, 15 },{ 15, 55 },{ 6, 22 },{ 40, 44 },{ 16, 35 },{ 1, 13 },{ 24, 9 },{ 42, 6 },{ 42, 22 },{ 57, 52 },{ 18, 21 },{ 18, 45 },{ 53 },{ 24, 54 },{ 20, 13 },{ 37, 22 },{ 10, 53 },{ 23, 55 },{ 56, 35 },{ 50, 4 },{ 51, 52 },{ 35, 37 },{ 57, 58 },{ 51, 35 },{ 4 },{ 53, 31 },{ 24, 25 },{ 35, 36 },{ 59, 47 },{ 36, 21 },{ 17, 42 },{ 44, 46 },{ 1, 52 },{ 40, 14 },{ 33, 59 },{ 39, 31 },{ 1, 44 },{ 8, 50 },{ 16, 38 },{ 54, 14 },{ 18, 5 },{ 56, 5 },{ 33, 43 },{ 35, 4 },{ 49, 53 },{ 49, 58 },{ 33, 38 },{ 41, 6 },{ 28, 55 },{ 56, 55 },{ 2, 4 },{ 25, 45 },{ 48, 19 },{ 56, 21 },{ 34, 30 },{ 8, 18 },{ 34, 19 },{ 11, 7 },{ 27, 38 },{ 40, 21 },{ 42, 12 },{ 35, 13 },{ 15, 7 },{ 0, 23 },{ 46, 47 },{ 8, 32 },{ 1, 27 },{ 37, 46 },{ 24, 10 },{ 58, 38 },{ 57, 45 } };
}


TEST_CLASS(TestSimpleEvaluator)
{
public:

	TEST_METHOD(whenEvaluateExampleIdThenReturnExpectedAverage)
	{
		createEvaluator(defaultData);
		const auto average = sut->evaluate(exampleId);
		Assert::AreEqual(expectedAverage, average);
	}

	TEST_METHOD(whenEvaluateExampleIdIsNotFoundThenReturnExpectedValue)
	{
		createEvaluator(defaultData);
		const auto average = sut->evaluate(invalidId);
		Assert::AreEqual(expectedAverageInCaseOfInvalid, average);
	}

	TEST_METHOD(whenEvaluateAllThenReturnExpectedAverageAtExampleElement)
	{
		createEvaluator(defaultData);
		const auto average = sut->evaluateAll().at(exampleId);
		Assert::AreEqual(expectedAverage, average);
	}

	TEST_METHOD(whenMassDataAquiredThenSortAndEvaluateCorrectly)
	{
		createEvaluator(twoIdData);
		const auto data = sut->evaluateAll();

		Assert::IsTrue(isApproximatelyEqual(expectedAverage1, data.front(), errorMargin));
		Assert::IsTrue(isApproximatelyEqual(expectedAverage2, data.back(), errorMargin));
	}

	bool isApproximatelyEqual(float value, float expectedValue, float margin)
	{
		return fabs(value - expectedValue) < value * margin;
	}

	void createEvaluator(DataContainer data) 
	{
		dataHandler = std::make_unique<MockHistoricDataHandler>(data);
		sut = std::make_unique<SimpleEvaluator>(dataHandler);
	}

private:
	std::unique_ptr<SimpleEvaluator> sut;
	std::unique_ptr<HistoricDataHandler> dataHandler;
};