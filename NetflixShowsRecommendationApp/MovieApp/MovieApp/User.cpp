#include "User.h"

User::User(DbUser&& dbUser) : DbUser{ std::forward<DbUser>(dbUser) }
{
	auto& storage = Database::GetInstance();
	int userId = GetUserId();
	m_WatchedList = storage.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetUserId, userId);
	m_WishList =  storage.GetWhereEqual<DbWishList>(&DbWishList::GetUserId, userId);
	m_PreferredCategories = storage.GetPreferredCategoriesForUser(userId);
}

std::vector<DbWatchedList> User::GetWatchedList() const
{
	auto& storage = Database::GetInstance();
	return storage.GetWhereEqual<DbWatchedList>(&DbWatchedList::GetUserId, GetUserId());
}

std::vector<DbWishList> User::GetWishList() const
{
	auto& storage = Database::GetInstance();
	return storage.GetWhereEqual<DbWishList>(&DbWishList::GetUserId, GetUserId());
}

std::vector<DbCategory> User::GetPreferredCategories() const
{
	auto& storage = Database::GetInstance();
	auto userCategoryRows = storage.GetWhereEqual<DbUserCategory>(&DbUserCategory::GetUserId, GetUserId());
	std::vector<DbCategory> categories;
	for (const auto& userCategoryRow : userCategoryRows)
	{
		categories.push_back(storage.Get<DbCategory>(userCategoryRow.GetCategoryId()));
	}
	return categories;
}
