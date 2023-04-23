#include "Show.h"

Show::Show(DbShow&& dbShow) : DbShow{ std::forward<DbShow>(dbShow) }
{
	auto& storage = Database::GetInstance();
	int showId = GetShowId();
	m_Directors = storage.GetDirectorsForShow(showId);
	m_Actors = storage.GetActorsForShow(showId);
	m_Categories = storage.GetCategoriesForShow(showId);
	m_Countries = storage.GetCountriesForShow(showId);
}

std::string Show::GetDirectors() const
{
	std::string directors;
	for (const auto& director : m_Directors)
	{
		directors += director;
		directors += ", ";
	}
	if (!directors.empty())
	{
		directors.pop_back();
		directors.pop_back();
	}
	return directors;
}

std::string Show::GetActors() const
{
	std::string actors;
	for (const auto& actor : m_Actors)
	{
		actors += actor;
		actors += ", ";
	}
	if (!actors.empty())
	{
		actors.pop_back();
		actors.pop_back();
	}
	return actors;
}

std::string Show::GetCategories() const
{
	std::string categories;
	for (const auto& category : m_Categories)
	{
		categories += category;
		categories += ", ";
	}
	if (!categories.empty())
	{
		categories.pop_back();
		categories.pop_back();
	}
	return categories;
}

std::string Show::GetCountries() const
{
	std::string countries;
	for (const auto& country : m_Countries)
	{
		countries += country;
		countries += ", ";
	}
	if (!countries.empty())
	{
		countries.pop_back();
		countries.pop_back();
	}
	return countries;
}
