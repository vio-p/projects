#include "Homepage.h"

Homepage::Homepage(QWidget* parent)
{
	ui.setupUi(this);
	m_MovieAppLogicPtr = nullptr;
	m_MenuIsOpen = true;
}

Homepage::Homepage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget* parent)
	: QDialog(parent)
{
	m_MovieAppLogicPtr = movieAppLogicPtr;
	m_MenuIsOpen = true;
	ui.setupUi(this);
	// homepage background
	QPixmap bkgnd("Resources/Pictures/background_homepage.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	// widget list palette
	QPalette pal = ui.listWidget->palette();
	pal.setColor(QPalette::Base, Qt::transparent);
	ui.listWidget->setPalette(pal);

	// connections
	connect(ui.MenuButton, SIGNAL(clicked()), SLOT(onMenuButtonClicked()));
	connect(ui.LogOutButton, SIGNAL(clicked()), SLOT(onLogOutButtonClicked()));
	connect(ui.WatchedListButton, SIGNAL(clicked()), SLOT(onWatchedListButtonClicked()));
	connect(ui.WishListButton, SIGNAL(clicked()), SLOT(onWishListButtonClicked()));
	connect(ui.MyProfileButton, SIGNAL(clicked()), SLOT(onMyProfileButtonClicked()));
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
	connect(ui.SearchButton, SIGNAL(clicked()), SLOT(onSearchButtonClicked()));
	AddItems();
}

Homepage::~Homepage()
{}

void Homepage::onMenuButtonClicked()
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

void Homepage::onLogOutButtonClicked()
{
	//std::shared_ptr<MovieAppFE> loginPage = std::make_shared<MovieAppFE>();
	MovieAppFE* loginPage = new MovieAppFE();
	loginPage->show();
	this->hide();
}

void Homepage::onWatchedListButtonClicked()
{
	//std::shared_ptr<WatchedList> watchedList = std::make_shared<WatchedList>(m_MovieAppLogicPtr);
	WatchedList* watchedList = new WatchedList(m_MovieAppLogicPtr);
	watchedList->show();
	this->hide();
}

void Homepage::onWishListButtonClicked()
{
	//std::shared_ptr<WishList> wishList = std::make_shared<WishList>(m_MovieAppLogicPtr);
	WishList* wishList = new WishList(m_MovieAppLogicPtr);
	wishList->show();
	this->hide();
}

void Homepage::onMyProfileButtonClicked()
{
	//std::shared_ptr<UserProfile> userProfile = std::make_shared<UserProfile>(m_MovieAppLogicPtr);
	UserProfile* userProfile = new UserProfile(m_MovieAppLogicPtr);
	userProfile->show();
	this->hide();
}

void Homepage::onItemDoubleClicked(QListWidgetItem* lwi)
{
	auto copil = ui.listWidget->currentItem();
	//std::shared_ptr<MoviePage> moviePage = std::make_shared<MoviePage>(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	MoviePage* moviePage = new MoviePage(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	moviePage->show();
	this->hide();
}

void Homepage::onSearchButtonClicked()
{
	//std::shared_ptr<SearchPage> searchPage = std::make_shared<SearchPage>(m_MovieAppLogicPtr);
	SearchPage* searchPage = new SearchPage(m_MovieAppLogicPtr);
	searchPage->show();
	this->hide();
}

void Homepage::AddItems()
{
	auto& storage = Database::GetInstance();
	auto recommendations = m_MovieAppLogicPtr->GetRecommendationsForUser();
	for (const auto& show : recommendations)
	{
		QWidget* w = new QWidget();

		QLabel* title = new QLabel(QString::fromStdString(show.GetTitle()));
		QLabel* id = new QLabel(QString::number(show.GetShowId()));
		id->setObjectName(QString::number(show.GetShowId()));

		QHBoxLayout* hb = new QHBoxLayout();

		id->setVisible(false);
		hb->addWidget(title);
		hb->addWidget(id);
		hb->setSizeConstraint(QLayout::SetFixedSize);
		w->setLayout(hb);

		QListWidgetItem* newItem = new QListWidgetItem();

		newItem->setSizeHint(w->sizeHint());
		ui.listWidget->addItem(newItem);
		ui.listWidget->setItemWidget(newItem, w);
		newItem->setData(Qt::UserRole, id->objectName());
	}
}
