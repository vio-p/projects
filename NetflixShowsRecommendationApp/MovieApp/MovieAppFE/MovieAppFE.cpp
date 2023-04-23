#include "MovieAppFE.h"

MovieAppFE::MovieAppFE(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//m_MovieAppLogicPtr = nullptr;

	//setting login background
	QPixmap bkgnd("Resources/Pictures/background_login_register.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	//setting components style
	InitCompStyleSheets();

	//buttons connections
	connect(ui.loginBtn, SIGNAL(clicked()), SLOT(onLoginButtonClicked()));
	connect(ui.registerBtn, SIGNAL(clicked()), SLOT(onRegisterButtonClicked()));
}

MovieAppFE::~MovieAppFE()
{
}

void MovieAppFE::InitCompStyleSheets()
{
	ui.usernameLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.passwordLbl->setStyleSheet("color: rgb(255, 255, 255);font: 700 9pt \"Segoe UI\";");
	ui.passwordLineEdit->setEchoMode(QLineEdit::Password);
	ui.loginBtn->setStyleSheet("background-color: rgb(255, 255, 255);");
	ui.registerBtn->setStyleSheet("background-color: rgb(255, 255, 255);");
}

void MovieAppFE::onLoginButtonClicked()
{
	QString usernameInput = ui.usernameLineEdit->text();
	if (usernameInput.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Username can't be empty");
		return;
	}
	if (!MovieAppLogic::FindUser(usernameInput.toStdString()))
	{
		QMessageBox::critical(this, "Error", "There is no user with this username. Register, then try again");
		return;
	}
	QString passwordInput = ui.passwordLineEdit->text();
	if (passwordInput.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Password can't be empty");
		return;
	}
	if (!MovieAppLogic::ValidatePassword(usernameInput.toStdString(), passwordInput.toStdString()))
	{
		QMessageBox::critical(this, "Error", "Wrong password");
		return;
	}
	//std::shared_ptr<Homepage> homepage = std::make_shared<Homepage>(std::make_shared<MovieAppLogic>(MovieAppLogic{ MovieAppLogic::GetDbUser(usernameInput.toStdString()) }));
	Homepage* homepage = new Homepage(std::make_shared<MovieAppLogic>(MovieAppLogic{ MovieAppLogic::GetDbUser(usernameInput.toStdString()) }));
	homepage->show();
	this->hide();
}

void MovieAppFE::onRegisterButtonClicked()
{
	//std::shared_ptr<RegisterF> registerWindow = std::make_shared<RegisterF>();
	RegisterF* registerWindow = new RegisterF();
	registerWindow->show();
	this->hide();
};