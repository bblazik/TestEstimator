#pragma once
#include "Evaluator.hpp"
#include "constants.h"
#include <tuple>
#include "HistoricDataHandler.hpp"
#include <map>

class SimpleEvaluator : public Evaluator
{
public:
	SimpleEvaluator(
		const std::unique_ptr<HistoricDataHandler>& historicDataHandler,
		float cutPercent = defaultValues::cutPercent,
		float additionPercent = defaultValues::additionPercent);
	float evaluate(unsigned id) override;
	std::vector<float> evaluateAll() override;

private:
	const DataContainer data;
	const float cutPercent;
	const float additionPercent;
	std::map<unsigned, DataContainer> segregatedData;

	const IteratorsPair calculateIteratorsAfterCut(const DataContainer& data) const;
	const float calculateAverage(DataContainer data) const;	
	const bool isDataAtIdValid(unsigned id);
};