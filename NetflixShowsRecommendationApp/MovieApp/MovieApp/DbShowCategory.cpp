#include "DbShowCategory.h"

DbShowCategory::DbShowCategory(int showId, int categoryId)
	: m_ShowId{ showId }, m_CategoryId{ categoryId }
{
}

int DbShowCategory::GetShowId() const
{
	return m_ShowId;
}

int DbShowCategory::GetCategoryId() const
{
	return m_CategoryId;
}

void DbShowCategory::SetShowId(int showId)
{
	m_ShowId = showId;
}

void DbShowCategory::SetCategoryId(int categoryId)
{
	m_CategoryId = categoryId;
}
