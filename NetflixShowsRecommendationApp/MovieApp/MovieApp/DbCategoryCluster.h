#pragma once
#include <string>

class DbCategoryCluster
{
	int m_ClusterId;
	std::string m_Centroid;
	std::string m_ClusterShowIds;

public:
	DbCategoryCluster() = default;
	DbCategoryCluster(int clusterId, const std::string& centroid, const std::string& clusterShowIds);

	int GetClusterId() const;
	std::string GetCentroid() const;
	std::string GetClusterShowIds() const;

	void SetClusterId(int clusterId);
	void SetCentroid(const std::string& centroid);
	void SetClusterShowIds(const std::string& clusterShowIds);
};

