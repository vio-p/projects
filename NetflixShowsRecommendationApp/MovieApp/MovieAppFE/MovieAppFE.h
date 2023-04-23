#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MovieAppFE.h"
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "RegisterF.h"
#include <QApplication>
#include <QBrush>
#include <QPalette>
#include "Homepage.h"
#include "UserProfile.h"
#include "MoviePage.h"

#include <memory>
#include "../MovieApp/MovieAppLogic.h"

class MovieAppFE : public QMainWindow
{
	Q_OBJECT

public:
	MovieAppFE(QWidget* parent = nullptr);
	~MovieAppFE();

private:
	Ui::MovieAppFEClass ui;
	void InitCompStyleSheets();

private slots:
	void onLoginButtonClicked();
	void onRegisterButtonClicked();
};
