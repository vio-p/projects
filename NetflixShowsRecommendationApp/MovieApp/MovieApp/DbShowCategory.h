#pragma once

class DbShowCategory
{
	int m_ShowId;
	int m_CategoryId;

public:
	DbShowCategory() = default;
	DbShowCategory(int showId, int categoryId);
	~DbShowCategory() = default;

	// getters
	int GetShowId() const;
	int GetCategoryId() const;

	// setters
	void SetShowId(int showId);
	void SetCategoryId(int categoryId);
};

