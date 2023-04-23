#pragma once
#include <string>

class DbShow
{
	int m_ShowId;
	std::string m_ShowType;
	std::string m_Title;
	std::string m_DateAdded;
	int m_ReleaseYear;
	std::string m_Rating;
	std::string m_Duration;
	std::string m_Description;
	float m_Stars;
	int m_NumberOfRatings;

public:
	DbShow() = default;
	DbShow(int showId,
		const std::string& showType,
		const std::string& title,
		const std::string& dateAdded,
		int releaseYear,
		const std::string& rating,
		const std::string& duration,
		const std::string& description);
	DbShow(const DbShow& other) = default;
	DbShow& operator=(const DbShow& other) = default;
	~DbShow() = default;

	DbShow& operator=(DbShow&& other);
	DbShow(DbShow&& other);

	int GetShowId() const;
	std::string GetType() const;
	int GetReleaseYear() const;
	std::string GetRating() const;
	std::string GetTitle() const;
	std::string GetDateAdded() const;
	std::string GetDuration() const;
	std::string GetDescription() const;
	float GetStars() const;
	int GetNumberOfRatings() const;

	void SetShowId(int showId);
	void SetType(const std::string& type);
	void SetReleaseYear(int releaseYear);
	void SetRating(const std::string& rating);
	void SetTitle(const std::string& title);
	void SetDateAdded(const std::string& dateAdded);
	void SetDuration(const std::string& duration);
	void SetDescription(const std::string& description);
	void SetStars(float stars);
	void SetNumberOfRatings(int numberOfRatings);
};