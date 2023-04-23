#include "DbShowCountry.h"

DbShowCountry::DbShowCountry(int showId, int countryId)
	: m_ShowId{ showId }, m_CountryId{ countryId }
{}

int DbShowCountry::GetShowId() const
{
	return m_ShowId;
}

int DbShowCountry::GetCountryId() const
{
	return m_CountryId;
}

void DbShowCountry::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShowCountry::SetCountryId(int countryId)
{
	m_CountryId = countryId;
}
