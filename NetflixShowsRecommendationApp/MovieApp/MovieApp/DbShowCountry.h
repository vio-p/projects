#pragma once

class DbShowCountry
{
	int m_ShowId;
	int m_CountryId;

public:
	DbShowCountry() = default;
	DbShowCountry(int showId, int countryId);
	~DbShowCountry() = default;

	// getters
	int GetShowId() const;
	int GetCountryId() const;

	// setters
	void SetShowId(int showId);
	void SetCountryId(int countryId);
};

