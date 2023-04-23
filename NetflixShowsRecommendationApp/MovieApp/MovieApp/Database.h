#pragma once
#include <iostream>
#include <fstream>
#include <sqlite_orm/sqlite_orm.h>
#include <unordered_set>
#include <queue>

#include "Utility.h"

#include "DbUser.h"
#include "DbShow.h"
#include "DbCategory.h"
#include "DbShowCategory.h"
#include "DbUserCategory.h"
#include "DbActor.h"
#include "DbShowActor.h"
#include "DbDirector.h"
#include "DbShowDirector.h"
#include "DbCountry.h"
#include "DbShowCountry.h"
#include "DbWishList.h"
#include "DbWatchedList.h"
#include "DbCategoryCluster.h"
#include "DbShowTokens.h"

using namespace sqlite_orm;

inline auto InitStorage(const std::string& path)
{
	using namespace sqlite_orm;
	return make_storage(path,
		make_table("user",
			make_column("user_id", &DbUser::SetUserId, &DbUser::GetUserId, autoincrement(), primary_key()),
			make_column("username", &DbUser::SetUsername, &DbUser::GetUsername),
			make_column("password", &DbUser::SetPassword, &DbUser::GetPassword),
			make_column("gender", &DbUser::SetGender, &DbUser::GetGender),
			make_column("birth_date", &DbUser::SetDateOfBirth, &DbUser::GetDateOfBirth)),
		make_table("show",
			make_column("show_id", &DbShow::SetShowId, &DbShow::GetShowId, autoincrement(), primary_key()),
			make_column("show_type", &DbShow::SetType, &DbShow::GetType),
			make_column("title", &DbShow::SetTitle, &DbShow::GetTitle),
			make_column("date_added", &DbShow::SetDateAdded, &DbShow::GetDateAdded),
			make_column("release_year", &DbShow::SetReleaseYear, &DbShow::GetReleaseYear),
			make_column("rating", &DbShow::SetRating, &DbShow::GetRating),
			make_column("duration", &DbShow::SetDuration, &DbShow::GetDuration),
			make_column("description", &DbShow::SetDescription, &DbShow::GetDescription),
			make_column("stars", &DbShow::SetStars, &DbShow::GetStars),
			make_column("number_of_ratings", &DbShow::SetNumberOfRatings, &DbShow::GetNumberOfRatings)),
		make_table("category",
			make_column("category_id", &DbCategory::SetCategoryId, &DbCategory::GetCategoryId, autoincrement(), primary_key()),
			make_column("category_name", &DbCategory::SetCategoryName, &DbCategory::GetCategoryName)),
		make_table("show_category",
			make_column("show_id", &DbShowCategory::SetShowId, &DbShowCategory::GetShowId),
			make_column("category_id", &DbShowCategory::SetCategoryId, &DbShowCategory::GetCategoryId),
			primary_key(&DbShowCategory::SetShowId, &DbShowCategory::SetCategoryId),
			foreign_key(&DbShowCategory::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbShowCategory::SetCategoryId).references(&DbCategory::SetCategoryId)),
		make_table("user_category",
			make_column("user_id", &DbUserCategory::SetUserId, &DbUserCategory::GetUserId),
			make_column("category_id", &DbUserCategory::SetCategoryId, &DbUserCategory::GetCategoryId),
			primary_key(&DbUserCategory::SetUserId, &DbUserCategory::SetCategoryId),
			foreign_key(&DbUserCategory::SetUserId).references(&DbUser::SetUserId),
			foreign_key(&DbUserCategory::SetCategoryId).references(&DbCategory::SetCategoryId)),
		make_table("actor",
			make_column("actor_id", &DbActor::SetActorId, &DbActor::GetActorId, autoincrement(), primary_key()),
			make_column("actor_name", &DbActor::SetActorName, &DbActor::GetActorName)),
		make_table("show_actor",
			make_column("show_id", &DbShowActor::SetShowId, &DbShowActor::GetShowId),
			make_column("actor_id", &DbShowActor::SetActorId, &DbShowActor::GetActorId),
			primary_key(&DbShowActor::SetShowId, &DbShowActor::SetActorId),
			foreign_key(&DbShowActor::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbShowActor::SetActorId).references(&DbActor::SetActorId)),
		make_table("director",
			make_column("director_id", &DbDirector::SetDirectorId, &DbDirector::GetDirectorId, autoincrement(), primary_key()),
			make_column("director_name", &DbDirector::SetDirectorName, &DbDirector::GetDirectorName)),
		make_table("show_director",
			make_column("show_id", &DbShowDirector::SetShowId, &DbShowDirector::GetShowId),
			make_column("director_id", &DbShowDirector::SetDirectorId, &DbShowDirector::GetDirectorId),
			primary_key(&DbShowDirector::SetShowId, &DbShowDirector::SetDirectorId),
			foreign_key(&DbShowDirector::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbShowDirector::SetDirectorId).references(&DbDirector::SetDirectorId)),
		make_table("country",
			make_column("country_id", &DbCountry::SetCountryId, &DbCountry::GetCountryId, autoincrement(), primary_key()),
			make_column("country_name", &DbCountry::SetCountryName, &DbCountry::GetCountryName)),
		make_table("show_country",
			make_column("show_id", &DbShowCountry::SetShowId, &DbShowCountry::GetShowId),
			make_column("country_id", &DbShowCountry::SetCountryId, &DbShowCountry::GetCountryId),
			primary_key(&DbShowCountry::SetShowId, &DbShowCountry::SetCountryId),
			foreign_key(&DbShowCountry::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbShowCountry::SetCountryId).references(&DbCountry::SetCountryId)),
		make_table("wish_list",
			make_column("show_id", &DbWishList::SetShowId, &DbWishList::GetShowId),
			make_column("user_id", &DbWishList::SetUserId, &DbWishList::GetUserId),
			make_column("date_added", &DbWishList::SetDateAdded, &DbWishList::GetDateAdded),
			primary_key(&DbWishList::SetShowId, &DbWishList::SetUserId),
			foreign_key(&DbWishList::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbWishList::SetUserId).references(&DbUser::SetUserId)),
		make_table("watched_list",
			make_column("show_id", &DbWatchedList::SetShowId, &DbWatchedList::GetShowId),
			make_column("user_id", &DbWatchedList::SetUserId, &DbWatchedList::GetUserId),
			make_column("play_count", &DbWatchedList::SetPlayCount, &DbWatchedList::GetPlayCount),
			make_column("last_time_watched", &DbWatchedList::SetLastTimeWatched, &DbWatchedList::GetLastTimeWatched),
			make_column("stars", &DbWatchedList::SetStars, &DbWatchedList::GetStars),
			primary_key(&DbWatchedList::SetShowId, &DbWatchedList::SetUserId),
			foreign_key(&DbWatchedList::SetShowId).references(&DbShow::SetShowId),
			foreign_key(&DbWatchedList::SetUserId).references(&DbUser::SetUserId)),
		make_table("category_cluster",
			make_column("cluster_id", &DbCategoryCluster::SetClusterId, &DbCategoryCluster::GetClusterId, primary_key()),
			make_column("centroid", &DbCategoryCluster::SetCentroid, &DbCategoryCluster::GetCentroid),
			make_column("cluster_show_ids", &DbCategoryCluster::SetClusterShowIds, &DbCategoryCluster::GetClusterShowIds)),
		make_table("show_tokens",
			make_column("show_id", &DbShowTokens::SetShowId, &DbShowTokens::GetShowId, primary_key()),
			make_column("tokens", &DbShowTokens::SetTokens, &DbShowTokens::GetTokens)));
}

using Storage = decltype(InitStorage(""));

class Database
{
	std::unique_ptr<Storage> m_StoragePtr;
	Database();
	static Database& Instance();

	void PopulateDatabase();
	void InitializeDatabaseShowTokens();

public:
	Database(Database&) = delete; // not cloneable 
	void operator=(const Database&) = delete; // not assignable
	static Database& GetInstance();
	static Database& SyncSchema();

	template<class T>
	static auto Insert(T element);

	template<class T>
	static void Replace(T element);

	template<class T>
	static void Remove(int id);

	template<class T>
	static auto Get(int id);

	template<class T>
	static auto GetAll();

	template<class T1, class T2, class T3>
	static auto GetWhereEqual(T2 element, T3 condition);

	template<class T>
	static auto CountAll();

	template<class T>
	static void Update(T element);

	std::unordered_set<std::string> GetDirectorsForShow(int showId);
	std::unordered_set<std::string> GetActorsForShow(int showId);
	std::unordered_set<std::string> GetCategoriesForShow(int showId);
	std::unordered_set<std::string> GetCountriesForShow(int showId);

	std::vector<DbCategory> GetPreferredCategoriesForUser(int userId);
	static std::vector<DbShow> SearchShows(const std::string& query);
};

template<class T>
inline auto Database::Insert(T element)
{
	auto& instance = Instance();
	return instance.m_StoragePtr->insert(element);
}

template<class T>
inline void Database::Replace(T element)
{
	auto& instance = Instance();
	instance.m_StoragePtr->replace(element);
}

template<class T>
inline void Database::Remove(int id)
{
	auto& instance = Instance();
	instance.m_StoragePtr->remove<T>(id);
}

template<class T>
inline auto Database::Get(int id)
{
	auto& instance = Instance();
	return instance.m_StoragePtr->get<T>(id);
}

template<class T>
inline auto Database::GetAll()
{
	auto& instance = Instance();
	return instance.m_StoragePtr->get_all<T>();
}

template<class T1, class T2, class T3>
inline auto Database::GetWhereEqual(T2 element, T3 condition)
{
	auto& instance = Instance();
	return instance.m_StoragePtr->get_all<T1>(where(c(element) == condition));
}

template<class T>
inline auto Database::CountAll()
{
	auto& instance = Database::Instance();
	return instance.m_StoragePtr->count<T>();
}

template<class T>
inline void Database::Update(T element)
{
	auto& instance = Database::Instance();
	instance.m_StoragePtr->update(element);
}


