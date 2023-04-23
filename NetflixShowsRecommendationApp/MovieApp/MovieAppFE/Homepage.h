#pragma once

#include <QDialog>
#include "ui_Homepage.h"
#include "qsplashscreen.h"
#include "qmovie.h"
#include "QHBoxLayout"

#include "MovieAppFE.h"
#include "WatchedList.h"
#include "SearchPage.h"

#include "../MovieApp/Database.h"
#include "../MovieApp/ShowBasedRG.h"

#include "../MovieApp/MovieAppLogic.h"

class Homepage : public QDialog
{
	Q_OBJECT

public:
	Homepage(QWidget* parent = nullptr);
	Homepage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget* parent = nullptr);
	~Homepage();

private:
	Ui::HomepageClass ui;
	bool m_MenuIsOpen;
	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;

	void AddItems();

private slots:
	void onMenuButtonClicked();
	void onLogOutButtonClicked();
	void onWatchedListButtonClicked();
	void onWishListButtonClicked();
	void onMyProfileButtonClicked();
	void onItemDoubleClicked(QListWidgetItem* lwi);
	void onSearchButtonClicked();
};
