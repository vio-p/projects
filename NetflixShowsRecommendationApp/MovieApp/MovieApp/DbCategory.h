#pragma once
#include <string>

class DbCategory
{
	int m_CategoryId;
	std::string m_CategoryName;

public:
	DbCategory() = default;
	DbCategory(int categoryId, const std::string& categoryName);
	~DbCategory() = default;

	// getters
	int GetCategoryId() const;
	std::string GetCategoryName() const;

	// setters
	void SetCategoryId(int categoryId);
	void SetCategoryName(const std::string& categoryName);
};

