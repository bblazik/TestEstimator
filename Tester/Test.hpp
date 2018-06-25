#pragma once

#include <string>
#include <sstream>
namespace dataStructures
{
	struct Test
	{
		unsigned id;		
		float excutionTime;
		
		friend bool operator==(const Test& lhs, const Test &rhs);
		friend std::istream& operator>>(std::istream& str, Test& data);
	};

}
