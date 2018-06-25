#pragma once

#include "HistoricDataHandler.hpp"
#include "constants.h"
#include "istream"

class CsvDataHandler : public HistoricDataHandler
{
public:
	CsvDataHandler(std::istream& stream) : stream(stream) {};
	DataContainer getData() override;
private:
	std::istream& stream;
};
