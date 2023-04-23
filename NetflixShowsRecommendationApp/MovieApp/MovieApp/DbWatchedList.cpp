#include "DbWatchedList.h"

DbWatchedList::DbWatchedList(int showId, int userId, int playCount, const std::string& lastTimeWatched, int stars)
	: m_ShowId{ showId },
	m_UserId{ userId },
	m_PlayCount{ playCount },
	m_LastTimeWatched{ lastTimeWatched },
	m_Stars{ stars }
{
}

int DbWatchedList::GetShowId() const
{
	return m_ShowId;
}

int DbWatchedList::GetUserId() const
{
	return m_UserId;
}

int DbWatchedList::GetPlayCount() const
{
	return m_PlayCount;
}

std::string DbWatchedList::GetLastTimeWatched() const
{
	return m_LastTimeWatched;
}

int DbWatchedList::GetStars() const
{
	return m_Stars;
}

void DbWatchedList::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbWatchedList::SetUserId(int userId)
{
	m_UserId = userId;
}


void DbWatchedList::SetPlayCount(int playCount)
{
	m_PlayCount = playCount;
}

void DbWatchedList::SetLastTimeWatched(const std::string& lastTimeWatched)
{
	m_LastTimeWatched = lastTimeWatched;
}

void DbWatchedList::SetStars(int stars)
{
	m_Stars = stars;
}
