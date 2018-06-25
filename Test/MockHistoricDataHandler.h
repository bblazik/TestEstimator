#pragma once

class MockHistoricDataHandler : public HistoricDataHandler
{
public:
	MockHistoricDataHandler(DataContainer& data) : data(data) {}

	DataContainer getData() 
	{
		return data;
	}
private:
	DataContainer &data;
};
