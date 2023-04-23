#pragma once

#include <QDialog>
#include "ui_WatchedList.h"
#include "UserProfile.h"
#include "WishList.h"
#include "MovieAppFE.h"

class WatchedList : public QDialog
{
	Q_OBJECT

public:
	WatchedList() = default;
	WatchedList(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent = nullptr);
	~WatchedList();

private:
	Ui::WatchedListClass ui;
	bool isMenuOpen = true;
	void AddWatchedMovies();
	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;

private slots:
	void onMenuButtonClicked();
	void onMyProfileButtonClicked();
	void onWishListButtonClicked();
	void onLogOutButtonClicked();
	void onHomepageButtonClicked();
	void onItemDoubleClicked(QListWidgetItem* lwi);
	void onSearchButtonClicked();
};
