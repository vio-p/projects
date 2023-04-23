#include "DbShowDirector.h"

DbShowDirector::DbShowDirector(int showId, int directorId)
	: m_ShowId{ showId }, m_DirectorId{ directorId }
{
}

int DbShowDirector::GetShowId() const
{
	return m_ShowId;
}

int DbShowDirector::GetDirectorId() const
{
	return m_DirectorId;
}

void DbShowDirector::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShowDirector::SetDirectorId(int directorId)
{
	m_DirectorId = directorId;
}
