#pragma once

#include <QDialog>
#include "ui_MoviePage.h"
#include <qmessagebox.h>
#include <qboxlayout.h>
#include "Homepage.h"

#include "../MovieApp/MovieAppLogic.h"
#include "../MovieApp/ShowBasedRG.h"

class MoviePage : public QDialog
{
	Q_OBJECT

public:
	MoviePage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, int showId, QWidget *parent = nullptr);
	~MoviePage();

private:
	Ui::MoviePageClass ui;
	int m_ShowId;
	std::shared_ptr<MovieAppLogic> m_MovieAppLogicPtr;
	int m_ShowRating;
	Show m_Show;

	void InitCompStyleSheets();
	void AddSimilarShows();

private slots:
	void onRateButtonClicked();
	void onAddWatchedButtonClicked();
	void onAddWishButtonClicked();
	void onItemDoubleClicked(QListWidgetItem* lwi);
	void onHomepageButtonClicked();
};
