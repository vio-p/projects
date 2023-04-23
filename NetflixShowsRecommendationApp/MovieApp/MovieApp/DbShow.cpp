#include "DbShow.h"

DbShow::DbShow(int showId, const std::string& showType, const std::string& title, const std::string& dateAdded, int releaseYear, const std::string& rating, const std::string& duration, const std::string& description)
	: m_ShowId{ showId },
	m_ShowType{ showType },
	m_Title{ title },
	m_DateAdded{ dateAdded },
	m_ReleaseYear{ releaseYear },
	m_Rating{ rating },
	m_Duration{ duration },
	m_Description{ description },
	m_Stars{ 0.0f },
	m_NumberOfRatings{ 0 }
{
}

DbShow& DbShow::operator=(DbShow&& other)
{
	m_ShowId = other.m_ShowId;
	m_ShowType = other.m_ShowType;
	m_Title = other.m_Title;
	m_DateAdded = other.m_DateAdded;
	m_ReleaseYear = other.m_ReleaseYear;
	m_Rating = other.m_Rating;
	m_Duration = other.m_Duration;
	m_Description = other.m_Description;
	m_Stars = other.m_Stars;
	m_NumberOfRatings = other.m_NumberOfRatings;
	new(&other) DbShow();
	return *this;
}

DbShow::DbShow(DbShow&& other)
{
	*this = std::move(other);
}

int DbShow::GetShowId() const
{
	return m_ShowId;
}

std::string DbShow::GetType() const
{
	return m_ShowType;
}

int DbShow::GetReleaseYear() const
{
	return m_ReleaseYear;
}

std::string DbShow::GetRating() const
{
	return m_Rating;
}

std::string DbShow::GetTitle() const
{
	return m_Title;
}

std::string DbShow::GetDateAdded() const
{
	return m_DateAdded;
}

std::string DbShow::GetDuration() const
{
	return m_Duration;
}

std::string DbShow::GetDescription() const
{
	return m_Description;
}

float DbShow::GetStars() const
{
	return m_Stars;
}

int DbShow::GetNumberOfRatings() const
{
	return m_NumberOfRatings;
}

void DbShow::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShow::SetType(const std::string& type)
{
	m_ShowType = type;
}

void DbShow::SetReleaseYear(int releaseYear)
{
	m_ReleaseYear = releaseYear;
}

void DbShow::SetRating(const std::string& rating)
{
	m_Rating = rating;
}

void DbShow::SetTitle(const std::string& title)
{
	m_Title = title;
}

void DbShow::SetDateAdded(const std::string& dateAdded)
{
	m_DateAdded = dateAdded;
}

void DbShow::SetDuration(const std::string& duration)
{
	m_Duration = duration;
}

void DbShow::SetDescription(const std::string& description)
{
	m_Description = description;
}

void DbShow::SetStars(float stars)
{
	m_Stars = stars;
}

void DbShow::SetNumberOfRatings(int numberOfRatings)
{
	m_NumberOfRatings = numberOfRatings;
}
