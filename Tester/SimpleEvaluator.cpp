#include "stdafx.h"
#include "SimpleEvaluator.h"
#include <iostream>
#include <algorithm>
#include <numeric>

SimpleEvaluator::SimpleEvaluator(const std::unique_ptr<HistoricDataHandler>& historicDataHandler, float cutPercent, float additionPercent) try:
	cutPercent(cutPercent),
	additionPercent(additionPercent),
	data(historicDataHandler->getData())	
{
	for (const auto& elem : data)
	{
		segregatedData[elem.id].push_back(elem);
	}
}
catch(std::istream::failure)
{
	std::cout << "Something go wrong with a input data";
};

std::vector<float> SimpleEvaluator::evaluateAll()
{
	std::vector<float> result;
	for (size_t i = 0u; i < segregatedData.size(); ++i)
	{
		result.push_back(evaluate(i));
	}
	return result;
};

float SimpleEvaluator::evaluate(unsigned id)
{	
	if (isDataAtIdValid(id))
	{
		const auto& concreteTestData = segregatedData[id];
		auto average = calculateAverage(concreteTestData);

		return (1.0f + average) * (1 + additionPercent); //Sample equations
	}
	return 0;
};

const bool SimpleEvaluator::isDataAtIdValid(unsigned id) 
{
	if (segregatedData.size() < id)
	{
		std::cout << "Id out of range: " << id;
		return false;
	}
	if (segregatedData[id].empty())
	{
		std::cout << "data for id: " << id << " was not founded";
		return false;
	}
	return true;
}

const float SimpleEvaluator::calculateAverage(DataContainer data) const
{
	std::sort(data.begin(), data.end(), [](auto elem1, auto elem2)
	{ return elem1.excutionTime > elem2.excutionTime; });

	const auto iterators = calculateIteratorsAfterCut(data);
	const auto numberOfElements = std::distance(iterators.first, iterators.second);
	const auto sum = std::accumulate(iterators.first, iterators.second, 0.0f,
		[](float currentSum, const auto& elem) {return currentSum + elem.excutionTime; });

	return sum/numberOfElements;
}

const IteratorsPair SimpleEvaluator::calculateIteratorsAfterCut(const DataContainer& data) const
{
	const auto size = data.size();
	const auto numberOfCutOutElements = int(size * cutPercent);

	const auto beginIt = data.begin() + numberOfCutOutElements;
	const auto endIt = data.begin() + (size - numberOfCutOutElements);

	return std::make_pair(beginIt, endIt);
}