#pragma once
#include <vector>
#include <iostream>
#include "Cluster.h"

template<class T>
class KMeans
{
private:
	std::vector<Cluster<T>> m_Clusters;
	uint16_t m_NumberOfClusters;
	uint16_t m_Iterations;

	void ClearClusters();
	uint16_t GetNearestClusterId(const Point<T>& point);

public:
	KMeans(const uint16_t& numberOfClusters, const uint16_t& iterations);

	// utility function
	static double ComputeEuclidianDistance(const Point<T>& firstPoint, const Point<T>& secondPoint);

	void Run(std::vector<Point<T>>& allPoints);

	Cluster<T> GetNearestCluster(const Point<T>& point) const;
	std::vector<Cluster<T>> GetClusters() const;
};

template<class T>
inline KMeans<T>::KMeans(const uint16_t& numberOfClusters, const uint16_t& iterations)
	: m_NumberOfClusters{ numberOfClusters }, m_Iterations{ iterations }
{}

template<class T>
inline void KMeans<T>::Run(std::vector<Point<T>>& allPoints)
{
	std::cout << "kmeans running...\n";
	size_t allPointsSize = allPoints.size();
	std::vector<uint16_t> usedPointIds;
	for (uint16_t clusterId = 0; clusterId < m_NumberOfClusters; clusterId++)
	{
		while (true)
		{
			uint16_t index = rand() % allPointsSize;
			if (find(usedPointIds.begin(), usedPointIds.end(), index) == usedPointIds.end())
			{
				usedPointIds.push_back(index);
				allPoints[index].SetClusterId(clusterId);
				Cluster<T> cluster(clusterId, allPoints[index]);
				m_Clusters.push_back(cluster);
				break;
			}
		}
	}
	uint16_t iteration = 0;
	while (true)
	{
		bool done = true;
		for (Point<T>& point : allPoints)
		{
			uint16_t currentClusterId = point.GetClusterId();
			uint16_t nearestClusterId = GetNearestClusterId(point);
			if (currentClusterId != nearestClusterId)
			{
				point.SetClusterId(nearestClusterId);
				done = false;
			}
		}
		ClearClusters();
		for (Point<T>& point : allPoints)
		{
			m_Clusters[point.GetClusterId()].AddPoint(point);
		}
		for (Cluster<T>& cluster : m_Clusters)
		{
			cluster.UpdateCentroid();
		}
		if (done || iteration == m_Iterations)
		{
			std::cout << "kmeans stopped running after " << iteration << " iterations\n";
			break;
		}
		iteration++;
	}
}

template<class T>
inline double KMeans<T>::ComputeEuclidianDistance(const Point<T>& firstPoint, const Point<T>& secondPoint)
{
	double sum = 0.0;
	std::vector<double> firstPointValues = firstPoint.GetValues();
	std::vector<double> secondPointValues = secondPoint.GetValues();
	for (size_t index = 0; index < firstPoint.GetPointSize(); index++)
	{
		sum += pow(secondPointValues[index] - firstPointValues[index], 2);
	}
	return sqrt(sum);
}

template<class T>
inline void KMeans<T>::ClearClusters()
{
	for (Cluster<T>& cluster : m_Clusters)
	{
		cluster.RemovePoints();
	}
}

template<class T>
inline uint16_t KMeans<T>::GetNearestClusterId(const Point<T>& point)
{
	double minDistance = std::numeric_limits<double>::max();
	uint16_t nearestClusterId = 0;
	for (const Cluster<T>& cluster : m_Clusters)
	{
		double distance = ComputeEuclidianDistance(cluster.GetCentroid(), point);
		if (minDistance > distance)
		{
			minDistance = distance;
			nearestClusterId = cluster.GetClusterId();
		}
	}
	return nearestClusterId;
}

template<class T>
inline Cluster<T> KMeans<T>::GetNearestCluster(const Point<T>& point) const
{
	return m_Clusters[GetNearestClusterId(point)];
}

template<class T>
inline std::vector<Cluster<T>> KMeans<T>::GetClusters() const
{
	return m_Clusters;
}
