#include "DbUserCategory.h"

DbUserCategory::DbUserCategory(int userId, int categoryId)
    : m_UserId{ userId }, m_CategoryId{ categoryId }
{
}

int DbUserCategory::GetCategoryId() const
{
    return m_CategoryId;
}

int DbUserCategory::GetUserId() const
{
    return m_UserId;
}

void DbUserCategory::SetCategoryId(int categoryId)
{
    m_CategoryId = categoryId;
}

void DbUserCategory::SetUserId(int userId)
{
    m_UserId = userId;
}
