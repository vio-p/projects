#pragma once

#include <QDialog>
#include "ui_UserPreferences.h"
#include "MovieAppFE.h"

class UserPreferences : public QDialog
{
	Q_OBJECT

public:
	UserPreferences(int newUserId, QWidget* parent = nullptr);
	~UserPreferences();

private:
	Ui::UserPreferencesClass ui;
	int m_NewUserId;
	void InitCompStyleSheets();

private slots:
	void onSubmitButtonClicked();
};
