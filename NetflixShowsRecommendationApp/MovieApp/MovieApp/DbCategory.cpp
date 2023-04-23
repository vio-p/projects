#include "DbCategory.h"

DbCategory::DbCategory(int categoryId, const std::string& categoryName)
	: m_CategoryId{ categoryId }, m_CategoryName{ categoryName }
{
}

int DbCategory::GetCategoryId() const
{
	return m_CategoryId;
}

std::string DbCategory::GetCategoryName() const
{
	return m_CategoryName;
}

void DbCategory::SetCategoryId(int categoryId)
{
	m_CategoryId = categoryId;
}

void DbCategory::SetCategoryName(const std::string& categoryName)
{
	m_CategoryName = categoryName;
}
