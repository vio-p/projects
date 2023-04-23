#pragma once

class DbShowDirector
{
	int m_ShowId;
	int m_DirectorId;

public:
	DbShowDirector() = default;
	DbShowDirector(int showId, int directorId);
	~DbShowDirector() = default;

	int GetShowId() const;
	int GetDirectorId() const;

	void SetShowId(int showId);
	void SetDirectorId(int directorId);
};
