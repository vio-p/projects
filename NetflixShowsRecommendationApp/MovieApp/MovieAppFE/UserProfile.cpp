#include "UserProfile.h"

UserProfile::UserProfile(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_MovieAppLogicPtr = movieAppLogicPtr;

	QPixmap bkgnd("Resources/Pictures/background_profile.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	QPixmap userPicture("Resources/Pictures/user_profile.jpg");
	ui.label_pic->setPixmap(userPicture);
	InitCompStyleSheets();

	QString username = "Username: " + QString::fromStdString(m_MovieAppLogicPtr->GetUsername());
	ui.label_Username->setText(username);

	//connections
	connect(ui.MenuButton, SIGNAL(clicked()), SLOT(onMenuButtonClicked()));
	connect(ui.HomepageButton, SIGNAL(clicked()), SLOT(onHomepageButtonClicked()));
	connect(ui.LogOutButton, SIGNAL(clicked()), SLOT(onLogOutButtonClicked()));
	connect(ui.WatchedListButton, SIGNAL(clicked()), SLOT(onWatchedListButtonClicked()));
	connect(ui.WishListButton, SIGNAL(clicked()), SLOT(onWishListButtonClicked()));
	connect(ui.SearchButton, SIGNAL(clicked()), SLOT(onSearchButtonClicked()));
	connect(ui.watchedList_button, SIGNAL(clicked()), SLOT(onWatchedListButtonClicked()));
	connect(ui.wishList_button, SIGNAL(clicked()), SLOT(onWishListButtonClicked()));
}

UserProfile::~UserProfile()
{}

void UserProfile::InitCompStyleSheets()
{
	ui.label->setStyleSheet("color: rgb(255, 255, 255);font: 800 14pt \"Segoe UI\";");
	ui.label_Username->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
}

void UserProfile::onMenuButtonClicked()
{
	if (m_MenuIsOpen)
	{
		ui.frame->setGeometry(10, 10, 131, 51);
		m_MenuIsOpen = false;
	}
	else
	{
		ui.frame->setGeometry(10, 10, 131, 371);
		m_MenuIsOpen = true;
	}
}

void UserProfile::onWishListButtonClicked()
{
	//std::shared_ptr<WishList> wishlist = std::make_shared<WishList>(m_MovieAppLogicPtr);
	WishList* wishList = new WishList(m_MovieAppLogicPtr);
	wishList->show();
	this->hide();
}

void UserProfile::onLogOutButtonClicked()
{
	MovieAppFE* login = new MovieAppFE();
	login->show();
	this->hide();
}

void UserProfile::onHomepageButtonClicked()
{
	//std::shared_ptr<Homepage> homepage = std::make_shared<Homepage>(m_MovieAppLogicPtr);
	Homepage* homepage = new Homepage(m_MovieAppLogicPtr);
	homepage->show();
	this->hide();
}

void UserProfile::onSearchButtonClicked()
{
	//std::shared_ptr<SearchPage> searchPage = std::make_shared<SearchPage>(m_MovieAppLogicPtr);
	SearchPage* searchPage = new SearchPage(m_MovieAppLogicPtr);
	searchPage->show();
	this->hide();
}

void UserProfile::onWatchedListButtonClicked()
{
	//std::shared_ptr<WatchedList> watchedList = std::make_shared<WatchedList>(m_MovieAppLogicPtr);
	WatchedList* watchedList = new WatchedList(m_MovieAppLogicPtr);
	watchedList->show();
	this->hide();
}