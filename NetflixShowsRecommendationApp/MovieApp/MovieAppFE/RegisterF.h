#pragma once

#include <QDialog>
#include "ui_RegisterF.h"
#include "UserPreferences.h"

class RegisterF : public QDialog
{
	Q_OBJECT

public:
	RegisterF(QWidget* parent = nullptr);
	~RegisterF();

private:
	Ui::RegisterFClass ui;
	void InitCompStyleSheets();
	bool InvalidInputs(QString username, QString password, char gender, QString dateOfBirth);

private slots:
	void onRegisterButtonClicked();
	void onBackToLoginButtonClicked();
};
