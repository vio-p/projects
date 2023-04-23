#pragma once
#include <memory>
#include "ShowBasedRG.h"
#include "UserBasedRG.h"

class RecommendationGenerator
{
	std::unique_ptr<IRecommendationGenerator> m_RecommendationGenerator;

public:
	RecommendationGenerator(const DbShow& show);
	RecommendationGenerator(const DbUser& user);
};

