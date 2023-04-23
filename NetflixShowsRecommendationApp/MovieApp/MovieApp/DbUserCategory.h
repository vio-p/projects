#pragma once

class DbUserCategory
{
	int m_CategoryId;
	int m_UserId;

public:
	DbUserCategory() = default;
	DbUserCategory(int userId, int categoryId);
	~DbUserCategory() = default;

	//getters
	int GetCategoryId() const;
	int GetUserId() const;

	//setters
	void SetCategoryId(int categoryId);
	void SetUserId(int userId);
};