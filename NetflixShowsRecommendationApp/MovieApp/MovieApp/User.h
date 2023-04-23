#pragma once
#include <vector>
#include "Database.h"

class User : public DbUser
{
	std::vector<DbWatchedList> m_WatchedList;
	std::vector<DbWishList> m_WishList;
	std::vector<DbCategory> m_PreferredCategories;

public:
	User() = default;
	User(DbUser&& dbUser);

	std::vector<DbWatchedList> GetWatchedList() const;
	std::vector<DbWishList> GetWishList() const;
	std::vector<DbCategory> GetPreferredCategories() const;
};

