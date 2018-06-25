#include "stdafx.h"
#include "CsvDataHandler.h"
#include <istream>
#include <iostream>

DataContainer CsvDataHandler::getData()
{	
	DataContainer data;
	dataStructures::Test test;

	while (stream >> test)
	{
		data.push_back(test);
	}
	if (data.empty())
	{
		std::cout << "Data is empty possible error";
	}
	stream.clear();
	stream.seekg(0, std::istream::beg);
	return data;
}