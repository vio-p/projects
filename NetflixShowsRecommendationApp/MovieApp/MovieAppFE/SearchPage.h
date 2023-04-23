#pragma once

#include <QDialog>
#include "ui_SearchPage.h"
#include "Homepage.h"
#include "WatchedList.h"
#include "WishList.h"
#include "MovieAppFE.h"
#include "UserProfile.h"

#include "../MovieApp/MovieAppLogic.h"

class SearchPage : public QDialog
{
	Q_OBJECT

public:
	SearchPage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent = nullptr);
	~SearchPage();

private:
	Ui::SearchPageClass ui;
	bool isMenuOpen = true;
	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;

private slots:
	void onMenuButtonClicked();
	void onLogOutButtonClicked();
	void onHomepageButtonClicked();
	void onWatchedListButtonClicked();
	void onWishListButtonClicked();
	void onMyProfileButtonClicked();
	void onItemDoubleClicked(QListWidgetItem* lwi);
	void onSearchButtonClicked();
};
