#pragma once
#include "IRecommendationGenerator.h"
#include "Database.h"
#include "KMeans.h"

class ShowBasedRG : public IRecommendationGenerator
{
	DbShow m_Show;
	std::vector<DbCategory> m_DbCategories;

	Point<DbShow> GetCategoryEmbedding(const DbShow& show);
	void SaveClusters(const std::vector<Cluster<DbShow>>& clusters);
	void InitializeDatabaseCategoryClusters();

public:
	ShowBasedRG(const DbShow& show);

	std::vector<DbShow> GetSimilarShowsByCategory();

	virtual DbShow GetRecommendation() override;
	virtual std::vector<DbShow> GetRecommendations(uint16_t numberOfRecommendations) override;
};
