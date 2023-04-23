#include "MovieAppLogic.h"

const Database& m_Database = Database::GetInstance();

MovieAppLogic::MovieAppLogic(DbUser&& dbUser)
{
	m_User = std::make_shared<User>(User(std::forward<DbUser>(dbUser)));
}

bool MovieAppLogic::FindUser(const std::string& username)
{
	auto users = m_Database.GetWhereEqual<DbUser>(&DbUser::GetUsername, username);
	return !users.empty();
}

bool MovieAppLogic::ValidatePassword(const std::string& username, const std::string& password)
{
	auto users = m_Database.GetWhereEqual<DbUser>(&DbUser::GetUsername, username);
	return users[0].GetPassword() == password;
}

std::string MovieAppLogic::GetCurrentDate()
{
	auto time = std::time(nullptr);
	auto localTime = *std::localtime(&time);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%d.%m.%Y");
	return oss.str();
}

int MovieAppLogic::RegisterUser(const std::string& username, const std::string& password, char gender, const std::string& dateOfBirth)
{
	return m_Database.Insert<DbUser>(DbUser{ -1, username, password, gender, dateOfBirth });
}

void MovieAppLogic::AddPreferredCategoriesForUser(int userId, const std::vector<std::string>& categories)
{
	auto dbCategories = m_Database.GetAll<DbCategory>();
	for (const auto& category : categories)
	{
		for (const auto& dbCategory : dbCategories)
		{
			if (dbCategory.GetCategoryName().find(category) != std::string::npos)
			{
				m_Database.Replace(DbUserCategory{ userId, dbCategory.GetCategoryId() });
			}
		}
	}
}

bool MovieAppLogic::IsStrong(const std::string& password)
{
	std::regex oneUpperCaseLetter{ "[A-Z]+" };
	std::regex oneLowerCaseLetter{ "[a-z]+" };
	std::regex oneDigit{ "[0-9]+" };
	std::regex oneSpecialCharacter{ "[!@#$%^&?]+" };
	return (regex_search(password, oneUpperCaseLetter)
		&& regex_search(password, oneLowerCaseLetter)
		&& regex_search(password, oneDigit)
		&& regex_search(password, oneSpecialCharacter)
		&& password.size() >= 8);
}

DbUser MovieAppLogic::GetDbUser(const std::string& username)
{
	auto users = m_Database.GetWhereEqual<DbUser>(&DbUser::GetUsername, username); // we know there's only gonna be one
	return users[0];
}

Show MovieAppLogic::GetShow(int showId)
{
	return Show{ m_Database.Get<DbShow>(showId) };
}

int MovieAppLogic::GetUserId()
{
	return m_User->GetUserId();
}

void MovieAppLogic::AddShowToWishList(int showId)
{
	m_Database.Replace(DbWishList{ showId, GetUserId(), MovieAppLogic::GetCurrentDate() });
}

std::string MovieAppLogic::AddShowToWatchedList(int showId, int rating)
{
	if (IsAlreadyInWatchedList(showId))
	{
		auto dbWatchedListRows = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetShowId, showId);
		for (auto& dbWatchedListRow : dbWatchedListRows)
		{
			if (dbWatchedListRow.GetUserId() == GetUserId())
			{
				dbWatchedListRow.SetLastTimeWatched(GetCurrentDate());
				int playCount = dbWatchedListRow.GetPlayCount();
				dbWatchedListRow.SetPlayCount(++playCount);
				dbWatchedListRow.SetStars(rating);
				m_Database.Replace(dbWatchedListRow);
				break;
			}
		}
	}
	else
	{
		// find solution for this
		/*if (IsAlreadyInWishList(showId))
		{
			DbWishList dbWishListRow = GetRowFromWishList(showId);

		}*/
		m_Database.Replace(DbWatchedList{ showId, GetUserId(), 1, GetCurrentDate(), rating });
	}
	DbWatchedList dbWatchedListRow = GetRowFromWatchedList(showId);
	std::string message = "You have watched this movie ";
	message += std::to_string(dbWatchedListRow.GetPlayCount());
	if (dbWatchedListRow.GetPlayCount() == 1)
	{
		message += " time ";
	}
	else
	{
		message += " times ";
	}
	message = message + "and you rated it " + std::to_string(rating) + " stars.";
	return message;
}

DbWatchedList MovieAppLogic::GetRowFromWatchedList(int showId)
{
	auto dbWatchedListRows = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetShowId, showId);
	for (const auto& dbWatchedListRow : dbWatchedListRows)
	{
		if (dbWatchedListRow.GetUserId() == GetUserId())
		{
			return dbWatchedListRow;
		}
	}
	return DbWatchedList{};
}

std::string MovieAppLogic::GetUsername()
{
	return m_User->GetUsername();
}

DbWishList MovieAppLogic::GetRowFromWishList(int showId)
{
	auto dbWishListRows = m_Database.GetWhereEqual<DbWishList>(&DbWishList::GetShowId, showId);
	for (const auto& dbWishListRow : dbWishListRows)
	{
		if (dbWishListRow.GetUserId() == GetUserId())
		{
			return dbWishListRow;
		}
	}
	return DbWishList{};
}

bool MovieAppLogic::IsAlreadyInWatchedList(int showId)
{
	auto dbWatchedListRows = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetShowId, showId);
	for (const auto& dbWatchedListRow : dbWatchedListRows)
	{
		if (dbWatchedListRow.GetUserId() == GetUserId())
		{
			return true;
		}
	}
	return false;
}

bool MovieAppLogic::IsAlreadyInWishList(int showId)
{
	auto dbWishListRows = m_Database.GetWhereEqual<DbWishList>(&DbWishList::GetShowId, showId);
	for (const auto& dbWishListRow : dbWishListRows)
	{
		if (dbWishListRow.GetUserId() == GetUserId())
		{
			return true;
		}
	}
	return false;
}

std::string MovieAppLogic::GetDateAddedToWishList(int showId)
{
	auto dbWishListRows = m_Database.GetWhereEqual<DbWishList>(&DbWishList::GetShowId, showId);
	for (const auto& dbWishListRow : dbWishListRows)
	{
		if (dbWishListRow.GetUserId() == GetUserId())
		{
			return dbWishListRow.GetDateAdded();
		}
	}
	return std::string();
}

std::vector<DbShow> MovieAppLogic::GetSimilarShows(int showId) // get back to this
{
	ShowBasedRG recGenerator(m_Database.Get<DbShow>(showId));
	return recGenerator.GetSimilarShowsByCategory();
}

std::string MovieAppLogic::GetDateLastWatched(int showId)
{
	auto dbWatchedListRows = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetShowId, showId);
	for (const auto& dbWatchedListRow : dbWatchedListRows)
	{
		if (dbWatchedListRow.GetUserId() == GetUserId())
		{
			return dbWatchedListRow.GetLastTimeWatched();
		}
	}
	return std::string();
}

std::vector<DbShow> MovieAppLogic::SearchShows(const std::string& query)
{
	return m_Database.SearchShows(query);
}

std::vector<DbShow> MovieAppLogic::GetWatchedShows()
{
	auto watchedList = m_User->GetWatchedList();
	std::vector<DbShow> shows;
	for (const auto& row : watchedList)
	{
		shows.push_back(m_Database.Get<DbShow>(row.GetShowId()));
	}
	return shows;
}

std::vector<DbShow> MovieAppLogic::GetWishList()
{
	auto wishList = m_User->GetWishList();
	std::vector<DbShow> shows;
	for (const auto& row : wishList)
	{
		shows.push_back(m_Database.Get<DbShow>(row.GetShowId()));
	}
	return shows;
}

std::vector<DbShow> MovieAppLogic::GetRecommendationsForUser()
{
	auto dbWatchedListRows = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetUserId, GetUserId());
	int maxPlayCount = 0;
	for (const auto& dbWatchedListRow : dbWatchedListRows)
	{
		if (dbWatchedListRow.GetPlayCount() > maxPlayCount)
		{
			maxPlayCount = dbWatchedListRow.GetPlayCount();
		}
	}
	auto mostPlayed = m_Database.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetPlayCount, maxPlayCount);
	std::vector<DbShow> recommendations;
	for (const auto& row : mostPlayed)
	{
		std::vector<DbShow> similarShows = GetSimilarShows(row.GetShowId());
		std::copy(similarShows.begin(), similarShows.end(), std::back_inserter(recommendations));
	}
	return recommendations;
}
