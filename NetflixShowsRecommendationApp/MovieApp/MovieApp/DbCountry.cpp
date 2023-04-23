#include "DbCountry.h"

DbCountry::DbCountry(int countryId, const std::string& countryName)
	: m_CountryId{ countryId }, m_CountryName{ countryName }
{}

int DbCountry::GetCountryId() const
{
	return m_CountryId;
}

std::string DbCountry::GetCountryName() const
{
	return m_CountryName;
}

void DbCountry::SetCountryName(const std::string& countryName)
{
	m_CountryName = countryName;
}

void DbCountry::SetCountryId(int countryId)
{
	m_CountryId = countryId;
}
