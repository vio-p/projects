#pragma once
#include <string>

class DbCountry
{
	int m_CountryId;
	std::string m_CountryName;

public:
	DbCountry() = default;
	DbCountry(int countryId, const std::string& countryName);
	~DbCountry() = default;

	// getters
	int GetCountryId() const;
	std::string GetCountryName() const;

	// setters
	void SetCountryName(const std::string& countryName);
	void SetCountryId(int countryId);
};

