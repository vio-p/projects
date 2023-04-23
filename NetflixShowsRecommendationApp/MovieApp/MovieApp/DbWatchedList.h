#pragma once
#include <string>

class DbWatchedList
{
	int m_ShowId;
	int m_UserId;
	int m_PlayCount;
	std::string m_LastTimeWatched;
	int m_Stars;

public:
	DbWatchedList() = default;
	DbWatchedList(int showId, int userId, int playCount, const std::string& lastTimeWatched, int stars);

	int GetShowId() const;
	int GetUserId() const;
	int GetPlayCount() const;
	std::string GetLastTimeWatched() const;
	int GetStars() const;

	void SetShowId(int showId);
	void SetUserId(int userId);
	void SetPlayCount(int playCount);
	void SetLastTimeWatched(const std::string& lastTimeWatched);
	void SetStars(int stars);
};