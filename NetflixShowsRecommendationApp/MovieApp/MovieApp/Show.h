#pragma once
#include <unordered_set>
#include "Database.h"

class Show : public DbShow
{
	std::unordered_set<std::string> m_Directors;
	std::unordered_set<std::string> m_Actors;
	std::unordered_set<std::string> m_Categories;
	std::unordered_set<std::string> m_Countries;

public:
	Show() = default;
	Show(DbShow&& dbShow);
	Show(const Show& other) = default;

	std::string GetDirectors() const;
	std::string GetActors() const;
	std::string GetCategories() const;
	std::string GetCountries() const;
};