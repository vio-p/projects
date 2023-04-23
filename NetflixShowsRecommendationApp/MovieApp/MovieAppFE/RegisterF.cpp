#include "RegisterF.h"
#include <qmessagebox.h>

RegisterF::RegisterF(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QPixmap bkgnd("Resources/Pictures/background_login_register.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	InitCompStyleSheets();
	connect(ui.backToLoginButton, SIGNAL(clicked()), SLOT(onBackToLoginButtonClicked()));
	connect(ui.registerButton, SIGNAL(clicked()), SLOT(onRegisterButtonClicked()));
}

RegisterF::~RegisterF()
{}

void RegisterF::InitCompStyleSheets()
{
	ui.usernameRLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.passwordRLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.passwordRLineEdit->setEchoMode(QLineEdit::Password);
	ui.maleRadio->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.femaleRadio->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.genderRLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.dateOfBirthRLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
}

bool RegisterF::InvalidInputs(QString username, QString password, char gender, QString dateOfBirth)
{
	return (username.isEmpty() || password.isEmpty() || gender == NULL || dateOfBirth.isEmpty());
}

void RegisterF::onBackToLoginButtonClicked()
{
	MovieAppFE* loginWindow = new MovieAppFE();
	loginWindow->show();
	this->hide();
}

void RegisterF::onRegisterButtonClicked()
{
	QString usernameInput = ui.usernameRLineEdit->text();
	QString passwordInput = ui.passwordRLineEdit->text();
	QString dateOfBirthInput = ui.dateEdit->text();
	char genderInput = NULL;
	if (ui.maleRadio->isChecked())
	{
		genderInput = 'm';
	}
	else if (ui.femaleRadio->isChecked())
	{
		genderInput = 'f';
	}
	if (InvalidInputs(usernameInput, passwordInput, genderInput, dateOfBirthInput))
	{
		QMessageBox::warning(this, "Warning", "Make sure inputs are not empty");
		return;
	}
	if (MovieAppLogic::FindUser(usernameInput.toStdString()))
	{
		QMessageBox::critical(this, "Error", "This username is not available");
		return;
	}
	if (!MovieAppLogic::IsStrong(passwordInput.toStdString()))
	{
		QMessageBox::critical(this, "Error", "This password is not strong enough.\nA strong password must have:\n* at least 8 characters\n* at least one uppercase letter\n* at least one lowercase letter\n* at least one digit\n* at least one special character");
		return;
	}
	int newUserId = MovieAppLogic::RegisterUser(usernameInput.toStdString(), passwordInput.toStdString(), genderInput, dateOfBirthInput.toStdString());
	UserPreferences* preferences = new UserPreferences(newUserId);
	preferences->show();
	this->hide();
}