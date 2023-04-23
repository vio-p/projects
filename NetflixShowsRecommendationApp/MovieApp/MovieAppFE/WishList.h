#pragma once

#include <QDialog>
#include "ui_WishList.h"
#include "Homepage.h"
#include "WatchedList.h"
#include "UserProfile.h"
#include "MovieAppFE.h"

#include "../MovieApp/MovieAppLogic.h"

class WishList : public QDialog
{
	Q_OBJECT

public:
	WishList(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent = nullptr);
	~WishList();

private:
	Ui::WishListClass ui;
	bool isMenuOpen = true;
	void AddWishListItems();

	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;

private slots:
	void onMenuButtonClicked();
	void onMyProfileButtonClicked();
	void onWatchedListButtonClicked();
	void onLogOutButtonClicked();
	void onHomepageButtonClicked();
	void onItemDoubleClicked(QListWidgetItem* lwi);
	void onSearchButtonClicked();
};
