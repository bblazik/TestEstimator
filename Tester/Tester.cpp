#pragma once

#include "stdafx.h"
#include <iostream>

#include "HistoricDataHandler.hpp"
#include "CsvDataHandler.h"

#include "Evaluator.hpp"
#include "SimpleEvaluator.h"

constexpr char sampleBuffer[] = "1,2\n1,3\n4,5\n2,3\n1,10\0";

template <typename T>
void print(T evaluationResults)
{
	int i = 0;
	for (const auto& x : evaluationResults)
	{
		std::cout << "id: " << i << " estimated value: " << x << "\n";
		++i;
	}
}

int main()
{
	//Aquaire data	
	std::istringstream sampleStream(sampleBuffer);
	std::unique_ptr<HistoricDataHandler> dataHandler = std::make_unique<CsvDataHandler>(sampleStream);

	//Evaluate data
	std::unique_ptr<Evaluator> evaluator = std::make_unique<SimpleEvaluator>(dataHandler);
	const auto evaluationResults = evaluator->evaluateAll();

	//Return output
	print(evaluationResults);
	
	system("pause");
    return 0;
}


