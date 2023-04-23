#pragma once
#include <vector>
#include <cstdint>
#include "DbShow.h"

class IRecommendationGenerator
{
public:
	virtual DbShow GetRecommendation() = 0;
	virtual std::vector<DbShow> GetRecommendations(uint16_t numberOfRecommendations) = 0;
};