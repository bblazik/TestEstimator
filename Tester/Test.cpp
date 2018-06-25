#include "stdafx.h"
#include "Test.hpp"
#include <iostream>

bool dataStructures::operator==(const Test& lhs, const Test &rhs)
{
	return lhs.id == rhs.id && lhs.excutionTime == rhs.excutionTime;
}

std::istream& dataStructures::operator>>(std::istream& str, Test& data)
{
	str.exceptions(std::istream::failbit | std::istream::badbit);
	try {
		std::string line, line2;	
		if (std::getline(str, line))
		{
			std::stringstream iss(line);
			if (std::getline(iss, line, ',') && std::getline(iss, line2, '\n'))
			{		
				data = std::move(Test({ std::stoul(line), std::stof(line2) }));
			}
			else
			{
				str.setstate(std::ios::failbit);
			}
		}
	}
	catch(const std::istream::failure&)
	{
		std::cout << "Exception opening/reading file";
	}
	return str;
}