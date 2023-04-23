#include "DbWishList.h"

DbWishList::DbWishList(int showId, int userId, const std::string& dateAdded)
	: m_ShowId{ showId }, m_UserId{ userId }, m_DateAdded{ dateAdded }
{}

int DbWishList::GetShowId() const
{
	return m_ShowId;
}

int DbWishList::GetUserId() const
{
	return m_UserId;
}

std::string DbWishList::GetDateAdded() const
{
	return m_DateAdded;
}

void DbWishList::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbWishList::SetUserId(int userId)
{
	m_UserId = userId;
}

void DbWishList::SetDateAdded(const std::string& dateAdded)
{
	m_DateAdded = dateAdded;
}
