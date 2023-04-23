#pragma once
#include "IRecommendationGenerator.h"
#include "DbUser.h"

class UserBasedRG : public IRecommendationGenerator
{
	DbUser m_User;

public:
	UserBasedRG(const DbUser& user);

	virtual DbShow GetRecommendation() override;
	virtual std::vector<DbShow> GetRecommendations(uint16_t numberOfRecommendations) override;
};

