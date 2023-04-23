#pragma once

#include <QDialog>
#include "ui_UserProfile.h"
#include "UserPreferences.h"

#include "../MovieApp/MovieAppLogic.h"

class UserProfile : public QDialog
{
	Q_OBJECT

public:
	UserProfile(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent = nullptr);
	~UserProfile();

private:
	Ui::UserProfileClass ui;
	void InitCompStyleSheets();
	bool m_MenuIsOpen = true;

	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;

private slots:
	void onMenuButtonClicked();
	void onWatchedListButtonClicked();
	void onWishListButtonClicked();
	void onLogOutButtonClicked();
	void onHomepageButtonClicked();
	void onSearchButtonClicked();
};
