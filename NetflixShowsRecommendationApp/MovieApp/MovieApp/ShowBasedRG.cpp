#include "ShowBasedRG.h"

#include "Utility.h"

Point<DbShow> ShowBasedRG::GetCategoryEmbedding(const DbShow& show)
{
	std::vector<double> pointValues;
	pointValues.resize(m_DbCategories.size(), 0);
	auto& storage = Database::GetInstance();
	std::vector<DbShowCategory> showCategories = storage.GetWhereEqual<DbShowCategory>(&DbShowCategory::GetShowId, show.GetShowId());
	for (const auto& showCategory : showCategories)
	{
		pointValues[static_cast<size_t>(showCategory.GetCategoryId()) - 1] = 1;
	}
	return Point<DbShow>{pointValues, show};
}

void ShowBasedRG::SaveClusters(const std::vector<Cluster<DbShow>>& clusters)
{
	auto& storage = Database::GetInstance();
	for (const auto& cluster : clusters)
	{
		Point<DbShow> centroid = cluster.GetCentroid();
		std::vector<double> values = centroid.GetValues();
		std::string centroidValues;
		for (const auto& value : values)
		{
			centroidValues += std::to_string(value);
			centroidValues += " ";
		}
		std::vector<Point<DbShow>> clusterPoints = cluster.GetPoints();
		std::string clusterShowIds;
		for (const auto& point : clusterPoints)
		{
			clusterShowIds += std::to_string(point.GetRepresentedObj().GetShowId());
			clusterShowIds += " ";
		}
		DbCategoryCluster categoryCluster{ static_cast<int>(cluster.GetClusterId()), centroidValues, clusterShowIds };
		storage.Insert<DbCategoryCluster>(categoryCluster);
	}
}

void ShowBasedRG::InitializeDatabaseCategoryClusters()
{
	auto& storage = Database::GetInstance();
	std::vector<DbCategoryCluster> dbCategoryClusters = storage.GetAll<DbCategoryCluster>();
	if (!dbCategoryClusters.empty())
	{
		return;
	}
	std::vector<DbShow> shows = storage.GetAll<DbShow>();
	std::vector<Point<DbShow>> points;
	for (const auto& show : shows)
	{
		points.emplace_back(GetCategoryEmbedding(show));
	}
	const uint16_t iterations = 1000;
	KMeans<DbShow> kMeans{ static_cast<uint16_t>(m_DbCategories.size()), iterations };
	kMeans.Run(points);
	std::vector<Cluster<DbShow>> clusters = kMeans.GetClusters();
	SaveClusters(clusters);
}

ShowBasedRG::ShowBasedRG(const DbShow& show)
{
	m_Show = show;
	auto& storage = Database::GetInstance();
	m_DbCategories = storage.GetAll<DbCategory>();
}

std::vector<DbShow> ShowBasedRG::GetSimilarShowsByCategory()
{
	InitializeDatabaseCategoryClusters();
	Point<DbShow> targetShowPoint = GetCategoryEmbedding(m_Show);
	auto& storage = Database::GetInstance();
	std::vector<DbCategoryCluster> dbCategoryClusters = storage.GetAll<DbCategoryCluster>();
	double minDistance = std::numeric_limits<double>::max();
	int nearestClusterId = 0;
	for (const auto& cluster : dbCategoryClusters)
	{
		Point<DbShow> centroid{ StringToVectorOfDoubleValues(cluster.GetCentroid()), DbShow() };
		double distance = KMeans<DbShow>::ComputeEuclidianDistance(targetShowPoint, centroid);
		if (distance < minDistance)
		{
			minDistance = distance;
			nearestClusterId = cluster.GetClusterId();
		}
	}
	std::vector<int> showIds = StringToVectorOfIntValues(dbCategoryClusters[static_cast<size_t>(nearestClusterId) - 1].GetClusterShowIds());
	std::vector<DbShow> similarShows;
	for (int id : showIds)
	{
		if (m_Show.GetShowId() == id)
		{
			continue;
		}
		similarShows.push_back(storage.Get<DbShow>(id));
	}
	return similarShows;
}

DbShow ShowBasedRG::GetRecommendation()
{
	return DbShow();
}

std::vector<DbShow> ShowBasedRG::GetRecommendations(uint16_t numberOfRecommendations)
{
	return std::vector<DbShow>();
}
