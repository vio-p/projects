#pragma once
#include <string>

class DbWishList
{
	int m_ShowId;
	int m_UserId;
	std::string m_DateAdded;

public:
	DbWishList() = default;
	DbWishList(int showId, int userId, const std::string& dateAdded);

	int GetShowId() const;
	int GetUserId() const;
	std::string GetDateAdded() const;

	void SetShowId(int showId);
	void SetUserId(int userId);
	void SetDateAdded(const std::string& dateAdded);
};

