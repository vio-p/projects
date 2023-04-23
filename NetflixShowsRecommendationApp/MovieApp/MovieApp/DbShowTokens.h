#pragma once
#include <string>

class DbShowTokens
{
	int m_ShowId;
	std::string m_Tokens;

public:
	DbShowTokens() = default;
	DbShowTokens(int showId, const std::string& tokens);
	~DbShowTokens() = default;

	int GetShowId() const;
	std::string GetTokens() const;

	void SetShowId(int showId);
	void SetTokens(const std::string& tokens);
};