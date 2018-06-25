#pragma once
#include <vector>
#include "Test.hpp"

using DataContainer = std::vector<dataStructures::Test>;
using IteratorsPair = std::pair<const DataContainer::const_iterator, const DataContainer::const_iterator>;

namespace defaultValues
{
	constexpr auto cutPercent = 0.1f;
	constexpr auto additionPercent = 0.1f;	
}











