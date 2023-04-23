#include "DbShowTokens.h"

DbShowTokens::DbShowTokens(int showId, const std::string& tokens)
	: m_ShowId{ showId }, m_Tokens{ tokens }
{
}

int DbShowTokens::GetShowId() const
{
	return m_ShowId;
}

std::string DbShowTokens::GetTokens() const
{
	return m_Tokens;
}

void DbShowTokens::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShowTokens::SetTokens(const std::string& tokens)
{
	m_Tokens = tokens;
}
