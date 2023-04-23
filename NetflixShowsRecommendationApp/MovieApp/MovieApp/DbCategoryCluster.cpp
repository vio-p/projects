#include "DbCategoryCluster.h"

DbCategoryCluster::DbCategoryCluster(int clusterId, const std::string& centroid, const std::string& clusterShowIds)
{
	m_ClusterId = clusterId;
	m_Centroid = centroid;
	m_ClusterShowIds = clusterShowIds;
}

int DbCategoryCluster::GetClusterId() const
{
	return m_ClusterId;
}

std::string DbCategoryCluster::GetCentroid() const
{
	return m_Centroid;
}

std::string DbCategoryCluster::GetClusterShowIds() const
{
	return m_ClusterShowIds;
}

void DbCategoryCluster::SetClusterId(int clusterId)
{
	m_ClusterId = clusterId;
}

void DbCategoryCluster::SetCentroid(const std::string& centroid)
{
	m_Centroid = centroid;
}

void DbCategoryCluster::SetClusterShowIds(const std::string& clusterShowIds)
{
	m_ClusterShowIds = clusterShowIds;
}
