#pragma once
#include <vector>
#include <memory>

template<class T>
class Point
{
private:
	std::vector<double> m_Values;
	size_t m_PointSize;
	uint16_t m_ClusterId;
	std::shared_ptr<T> m_RepresentedObj;

public:
	Point() = default;
	Point(const std::vector<double>& values, const T& representedObj);
	Point(const Point<T>& other);

	uint16_t GetClusterId() const;
	size_t GetPointSize() const;
	std::vector<double> GetValues() const;
	T GetRepresentedObj() const;

	void SetClusterId(const uint16_t& clusterId);
	void SetValues(const std::vector<double>& values);
};

template<class T>
class Cluster
{
private:
	uint16_t m_ClusterId;
	std::vector<Point<T>> m_Points;
	Point<T> m_Centroid;

public:
	Cluster(const uint16_t& clusterId, Point<T>& centroid);

	void AddPoint(Point<T>& point);
	void UpdateCentroid();
	void RemovePoints();

	std::vector<Point<T>> GetPoints() const;
	uint16_t GetClusterId() const;
	size_t GetClusterSize() const;
	Point<T> GetCentroid() const;
};

template<class T>
inline Point<T>::Point(const std::vector<double>& values, const T& representedObj)
	: m_Values{ values }, m_RepresentedObj{ std::make_shared<T>(representedObj) }, m_PointSize{ values.size() }
{}

template<class T>
inline Point<T>::Point(const Point<T>& other)
{
	m_Values = other.m_Values;
	m_PointSize = other.m_PointSize;
	m_ClusterId = other.m_ClusterId;
	m_RepresentedObj = other.m_RepresentedObj;
}

template<class T>
inline uint16_t Point<T>::GetClusterId() const
{
	return m_ClusterId;
}

template<class T>
inline size_t Point<T>::GetPointSize() const
{
	return m_PointSize;
}

template<class T>
inline std::vector<double> Point<T>::GetValues() const
{
	return m_Values;
}

template<class T>
inline T Point<T>::GetRepresentedObj() const
{
	return *m_RepresentedObj;
}

template<class T>
inline void Point<T>::SetClusterId(const uint16_t& clusterId)
{
	m_ClusterId = clusterId;
}

template<class T>
inline void Point<T>::SetValues(const std::vector<double>& values)
{
	m_Values = values;
}

template<class T>
inline Cluster<T>::Cluster(const uint16_t& clusterId, Point<T>& centroid)
	: m_ClusterId{ clusterId }, m_Centroid{ centroid }
{
	AddPoint(centroid);
}

template<class T>
inline void Cluster<T>::AddPoint(Point<T>& point)
{
	point.SetClusterId(m_ClusterId);
	m_Points.push_back(point);
}

template<class T>
inline void Cluster<T>::UpdateCentroid()
{
	if (m_Points.empty())
	{
		return;
	}
	std::vector<double> sumOfPoints;
	size_t pointSize = m_Centroid.GetPointSize();
	sumOfPoints.resize(pointSize, 0.0);
	for (const Point<T>& point : m_Points)
	{
		std::vector<double> pointValues = point.GetValues();
		for (size_t index = 0; index < pointSize; index++)
		{
			sumOfPoints[index] += pointValues[index];
		}
	}
	std::vector<double> auxiliary;
	std::copy(sumOfPoints.begin(), sumOfPoints.end(), std::back_inserter(auxiliary));
	for (auto& element : auxiliary)
	{
		element /= m_Points.size();
	}
	m_Centroid.SetValues(auxiliary);
}

template<class T>
inline void Cluster<T>::RemovePoints()
{
	m_Points.clear();
}

template<class T>
inline std::vector<Point<T>> Cluster<T>::GetPoints() const
{
	return m_Points;
}

template<class T>
inline uint16_t Cluster<T>::GetClusterId() const
{
	return m_ClusterId;
}

template<class T>
inline size_t Cluster<T>::GetClusterSize() const
{
	return m_Points.size();
}

template<class T>
inline Point<T> Cluster<T>::GetCentroid() const
{
	return m_Centroid;
}
