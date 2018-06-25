#pragma once
#include "constants.h"
#include <vector>

class Evaluator
{
public:	
	virtual float evaluate(unsigned id) = 0;
	virtual std::vector<float> evaluateAll() = 0;
	virtual ~Evaluator() = default;
};