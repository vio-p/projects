#include "DbDirector.h"

DbDirector::DbDirector(int directorId, const std::string& directorName)
    : m_DirectorId{ directorId }, m_DirectorName{ directorName }
{
}

int DbDirector::GetDirectorId() const
{
    return m_DirectorId;
}

std::string DbDirector::GetDirectorName() const
{
    return m_DirectorName;
}

void DbDirector::SetDirectorId(int directorId)
{
    m_DirectorId = directorId;
}

void DbDirector::SetDirectorName(const std::string& directorName)
{
    m_DirectorName = directorName;
}
