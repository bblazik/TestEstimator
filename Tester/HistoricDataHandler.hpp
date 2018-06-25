#pragma once
#include "constants.h"

class HistoricDataHandler
{
public:
	virtual DataContainer getData() = 0;
	virtual ~HistoricDataHandler() = default;
};


