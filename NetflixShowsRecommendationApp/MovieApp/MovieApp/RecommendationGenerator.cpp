#include "RecommendationGenerator.h"

RecommendationGenerator::RecommendationGenerator(const DbShow& show)
{
	m_RecommendationGenerator = std::make_unique<ShowBasedRG>(show);
}

RecommendationGenerator::RecommendationGenerator(const DbUser& user)
{
	m_RecommendationGenerator = std::make_unique<UserBasedRG>(user);
}
