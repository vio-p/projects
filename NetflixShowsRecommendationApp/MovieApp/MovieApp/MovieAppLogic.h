#pragma once

#include "User.h"
#include "Show.h"
#include "ShowBasedRG.h"

#include <regex>
#include <ctime>
#include <iomanip>

class MovieAppLogic
{
	std::shared_ptr<User> m_User; // this was unique_ptr originally but ran into problems when trying to use shared_ptr<MovieAppLogic> (deleted copy constructor)
	static const Database& m_Database;

public:
	MovieAppLogic() = default;
	MovieAppLogic(DbUser&& dbUser);
	MovieAppLogic(const MovieAppLogic& other) = default;
	~MovieAppLogic() = default;

	static std::string GetCurrentDate();

	static bool FindUser(const std::string& username);
	static bool ValidatePassword(const std::string& username, const std::string& password);

	// returns the id of the new user
	static int RegisterUser(const std::string& username, const std::string& password, char gender, const std::string& dateOfBirth);
	static bool IsStrong(const std::string& password);
	static void AddPreferredCategoriesForUser(int userId, const std::vector<std::string>& categories);

	static DbUser GetDbUser(const std::string& username);
	static Show GetShow(int showId);

	int GetUserId();
	std::string GetUsername();
	void AddShowToWishList(int showId);
	DbWatchedList GetRowFromWatchedList(int showId);
	DbWishList GetRowFromWishList(int showId);
	std::string AddShowToWatchedList(int showId, int rating);

	bool IsAlreadyInWatchedList(int showId);
	std::string GetDateAddedToWishList(int showId);
	std::string GetDateLastWatched(int showId);
	bool IsAlreadyInWishList(int showId);

	static std::vector<DbShow> GetSimilarShows(int showId);
	static std::vector<DbShow> SearchShows(const std::string& query);

	std::vector<DbShow> GetWatchedShows();
	std::vector<DbShow> GetWishList();

	std::vector<DbShow> GetRecommendationsForUser();
};

