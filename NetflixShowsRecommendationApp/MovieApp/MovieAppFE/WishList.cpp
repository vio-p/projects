#include "WishList.h"

WishList::WishList(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_MovieAppLogicPtr = movieAppLogicPtr;

	QPixmap bkgnd("Resources/Pictures/background_wishlist_watchedList");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	QPalette pal = ui.listWidget->palette();
	pal.setColor(QPalette::Base, Qt::transparent);
	ui.listWidget->setPalette(pal);

	//connections
	connect(ui.MenuButton, SIGNAL(clicked()), SLOT(onMenuButtonClicked()));
	connect(ui.HomepageButton, SIGNAL(clicked()), SLOT(onHomepageButtonClicked()));
	connect(ui.LogOutButton, SIGNAL(clicked()), SLOT(onLogOutButtonClicked()));
	connect(ui.WatchedListButton, SIGNAL(clicked()), SLOT(onWatchedListButtonClicked()));
	connect(ui.MyProfileButton, SIGNAL(clicked()), SLOT(onMyProfileButtonClicked()));
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
	connect(ui.SearchButton, SIGNAL(clicked()), SLOT(onSearchButtonClicked()));

	AddWishListItems();
}

WishList::~WishList()
{}

void WishList::AddWishListItems()
{
	auto& storage = Database::GetInstance();
	std::vector<DbShow> wishList = m_MovieAppLogicPtr->GetWishList();
	for (const auto& wishedShow : wishList)
	{
		QWidget* w = new QWidget();

		QLabel* title = new QLabel(QString::fromStdString(wishedShow.GetTitle()));
		QLabel* id = new QLabel(QString::number(wishedShow.GetShowId()));
		id->setObjectName(QString::number(wishedShow.GetShowId()));

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

void WishList::onHomepageButtonClicked()
{
	//std::shared_ptr<Homepage> homepage = std::make_shared<Homepage>(m_MovieAppLogicPtr);
	Homepage* homepage = new Homepage(m_MovieAppLogicPtr);
	homepage->show();
	this->hide();
}

void WishList::onMyProfileButtonClicked()
{
	//std::shared_ptr<UserProfile> profile = std::make_shared<UserProfile>(m_MovieAppLogicPtr);
	UserProfile* profile = new UserProfile(m_MovieAppLogicPtr);
	profile->show();
	this->hide();
}

void WishList::onWatchedListButtonClicked()
{
	//std::shared_ptr<WatchedList> watchedList = std::make_shared<WatchedList>(m_MovieAppLogicPtr);
	WatchedList* watchedList = new WatchedList(m_MovieAppLogicPtr);
	watchedList->show();
	this->hide();
}

void WishList::onLogOutButtonClicked()
{
	//std::shared_ptr<MovieAppFE> login = std::make_shared<MovieAppFE>();
	MovieAppFE* login = new MovieAppFE();
	login->show();
	this->hide();
}

void WishList::onMenuButtonClicked()
{
	if (isMenuOpen)
	{
		ui.frame->setGeometry(10, 10, 131, 51);
		isMenuOpen = false;
	}
	else
	{
		ui.frame->setGeometry(10, 10, 131, 371);
		isMenuOpen = true;
	}
}

void WishList::onItemDoubleClicked(QListWidgetItem* lwi)
{
	auto copil = ui.listWidget->currentItem();
	//std::shared_ptr<MoviePage> moviePage = std::make_shared<MoviePage>(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	MoviePage* moviePage = new MoviePage(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	moviePage->show();
	this->hide();
}

void WishList::onSearchButtonClicked()
{
	//std::shared_ptr<SearchPage> searchPage = std::make_shared<SearchPage>(m_MovieAppLogicPtr);
	SearchPage* searchPage = new SearchPage(m_MovieAppLogicPtr);
	searchPage->show();
	this->hide();
}
