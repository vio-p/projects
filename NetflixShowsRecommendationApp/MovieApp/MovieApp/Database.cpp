#include "Database.h"

Database::Database()
{
	m_StoragePtr = std::make_unique<Storage>(InitStorage("Resources/MovieApp.db"));
	m_StoragePtr->sync_schema();
	std::vector shows = m_StoragePtr->get_all<DbShow>();
	if (shows.empty())
	{
		PopulateDatabase();
	}
	int showTokensRows = m_StoragePtr->count<DbShowTokens>();
	if (!showTokensRows)
	{
		InitializeDatabaseShowTokens();
	}
}

Database& Database::Instance()
{
	static std::unique_ptr<Database> instance(new Database);
	return *instance;
}

void Database::PopulateDatabase()
{
	std::ifstream file("Resources/netflix_titles.csv");
	std::string line;
	getline(file, line); // skips the first line
	while (!file.eof())
	{
		getline(file, line);
		std::vector<std::string> splitLine = SplitCsvLine(line);
		DbShow show{ -1, splitLine[1], splitLine[2], splitLine[6], std::stoi(splitLine[7]), splitLine[8], splitLine[9], splitLine[11] };
		int insertedShowId = m_StoragePtr->insert(show);
		std::cout << insertedShowId << std::endl;
		std::vector<std::string> directors = SplitString(splitLine[3], ", ");
		for (const std::string& director : directors)
		{
			int directorId;
			std::vector<DbDirector> dbDirectors = m_StoragePtr->get_all<DbDirector>(where(c(&DbDirector::SetDirectorName) == director));
			if (dbDirectors.empty())
			{
				DbDirector newDirector{ -1, director };
				directorId = m_StoragePtr->insert(newDirector);
			}
			else
			{
				directorId = dbDirectors[0].GetDirectorId();
			}
			DbShowDirector showDirector{ insertedShowId, directorId };
			m_StoragePtr->replace(showDirector);
		}
		std::vector<std::string> actors = SplitString(splitLine[4], ", ");
		for (const std::string& actor : actors)
		{
			int actorId;
			std::vector<DbActor> dbActors = m_StoragePtr->get_all<DbActor>(where(c(&DbActor::SetActorName) == actor));
			if (dbActors.empty())
			{
				DbActor newActor{ -1, actor };
				actorId = m_StoragePtr->insert(newActor);
			}
			else
			{
				actorId = dbActors[0].GetActorId();
			}
			DbShowActor showActor{ insertedShowId, actorId };
			m_StoragePtr->replace(showActor);
		}
		std::vector<std::string> categories = SplitString(splitLine[10], ", ");
		for (const std::string& category : categories)
		{
			int categoryId;
			std::vector<DbCategory> dbCategories = m_StoragePtr->get_all<DbCategory>(where(c(&DbCategory::SetCategoryName) == category));
			if (dbCategories.empty())
			{
				DbCategory newCategory{ -1, category };
				categoryId = m_StoragePtr->insert(newCategory);
			}
			else
			{
				categoryId = dbCategories[0].GetCategoryId();
			}
			DbShowCategory showCategory{ insertedShowId, categoryId };
			m_StoragePtr->replace(showCategory);
		}
		std::vector<std::string> countries = SplitString(splitLine[5], ", ");
		for (const std::string& country : countries)
		{
			int countryId;
			std::vector<DbCountry> dbCountries = m_StoragePtr->get_all<DbCountry>(where(c(&DbCountry::SetCountryName) == country));
			if (dbCountries.empty())
			{
				DbCountry newCountry{ -1, country };
				countryId = m_StoragePtr->insert(newCountry);
			}
			else
			{
				countryId = dbCountries[0].GetCountryId();
			}
			DbShowCountry showCountry{ insertedShowId, countryId };
			m_StoragePtr->replace(showCountry);
		}
	}
}

void Database::InitializeDatabaseShowTokens()
{
	int numberOfShows = m_StoragePtr->count<DbShow>();
	for (int showId = 1; showId <= numberOfShows; showId++)
	{
		std::cout << showId << " ";
		std::string tokens;
		DbShow show = m_StoragePtr->get<DbShow>(showId);
		std::string showTitle = show.GetTitle();
		tokens += ToLowerCase(showTitle);;
		tokens += " ";
		std::string showDescription = show.GetDescription();
		tokens += ToLowerCase(showDescription);
		tokens += " ";
		auto showActors = GetActorsForShow(showId);
		for (const auto& actor : showActors)
		{
			tokens += ToLowerCase(actor);
			tokens += " ";
		}
		auto showDirectors = GetDirectorsForShow(showId);
		for (const auto& director : showDirectors)
		{
			tokens += ToLowerCase(director);
			tokens += " ";
		}
		auto showCountries = GetCountriesForShow(showId);
		for (const auto& country : showCountries)
		{
			tokens += ToLowerCase(country);
			tokens += " ";
		}
		auto showCategories = GetCategoriesForShow(showId);
		for (const auto& category : showCategories)
		{
			tokens += ToLowerCase(category);
			tokens += " ";
		}
		DbShowTokens showTokens{ showId, tokens };
		m_StoragePtr->insert<DbShowTokens>(showTokens);
	}
}

Database& Database::GetInstance()
{
	return Instance();
}

Database& Database::SyncSchema()
{
	auto& instance = Instance();
	instance.m_StoragePtr->sync_schema();
	return instance;
}

std::unordered_set<std::string> Database::GetDirectorsForShow(int showId)
{
	auto showDirectors = m_StoragePtr->select((&DbDirector::SetDirectorName),
		inner_join<DbShowDirector>(on(c(&DbDirector::SetDirectorId) == &DbShowDirector::SetDirectorId)),
		inner_join<DbShow>(on(c(&DbShowDirector::SetShowId) == &DbShow::SetShowId)), where(c(&DbShow::SetShowId) == showId));
	return std::unordered_set(showDirectors.begin(), showDirectors.end());
}

std::unordered_set<std::string> Database::GetActorsForShow(int showId)
{
	auto showActors = m_StoragePtr->select((&DbActor::SetActorName),
		inner_join<DbShowActor>(on(c(&DbActor::SetActorId) == &DbShowActor::SetActorId)),
		inner_join<DbShow>(on(c(&DbShowActor::SetShowId) == &DbShow::SetShowId)), where(c(&DbShow::SetShowId) == showId));
	return std::unordered_set(showActors.begin(), showActors.end());
}

std::unordered_set<std::string> Database::GetCategoriesForShow(int showId)
{
	auto showCategories = m_StoragePtr->select((&DbCategory::SetCategoryName),
		inner_join<DbShowCategory>(on(c(&DbCategory::SetCategoryId) == &DbShowCategory::SetCategoryId)),
		inner_join<DbShow>(on(c(&DbShowCategory::SetShowId) == &DbShow::SetShowId)), where(c(&DbShow::SetShowId) == showId));
	return std::unordered_set(showCategories.begin(), showCategories.end());
}

std::unordered_set<std::string> Database::GetCountriesForShow(int showId)
{
	auto showCountries = m_StoragePtr->select((&DbCountry::SetCountryName),
		inner_join<DbShowCountry>(on(c(&DbCountry::SetCountryId) == &DbShowCountry::SetCountryId)),
		inner_join<DbShow>(on(c(&DbShowCountry::SetShowId) == &DbShow::SetShowId)), where(c(&DbShow::SetShowId) == showId));
	return std::unordered_set(showCountries.begin(), showCountries.end());
}

std::vector<DbCategory> Database::GetPreferredCategoriesForUser(int userId)
{
	auto userCategories = GetWhereEqual<DbUserCategory>(&DbUserCategory::GetUserId, userId);
	std::vector<DbCategory> categories;
	for (const auto& userCategory : userCategories)
	{
		categories.push_back(Get<DbCategory>(userCategory.GetCategoryId()));
	}
	return categories;
}

std::vector<DbShow> Database::SearchShows(const std::string& query)
{
	auto& database = Database::Instance();
	auto showCount = database.CountAll<DbShow>();
	auto words = SplitIntoWords(query);
	for (auto& word : words)
	{
		word = ToLowerCase(word);
	}
	std::unordered_set<std::string> wordSet(words.begin(), words.end());
	using CustomPair = std::pair<uint8_t, DbShow>;
	auto compare = [](const CustomPair& a, const CustomPair& b) { return a.first < b.first; };
	std::priority_queue<CustomPair, std::vector<CustomPair>, decltype(compare)> result(compare);
	for (int id = 1; id <= showCount; id++)
	{
		auto show = database.Get<DbShowTokens>(id);
		uint8_t count = 0;
		for (const auto& word : wordSet)
		{
			if (PredictiveSearch(show.GetTokens(), word))
			{
				count++;
			}
			std::string title = ToLowerCase(database.Get<DbShow>(id).GetTitle());
			if (title.find(word) != std::string::npos)
			{
				count += 5;
			}
		}
		if (count > 0)
		{
			result.push({ count, database.Get<DbShow>(id) });
		}
	}
	std::vector<DbShow> shows;
	while (!result.empty())
	{
		shows.push_back(result.top().second);
		result.pop();
	}
	return shows;
}