#include "SearchPage.h"

SearchPage::SearchPage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
    m_MovieAppLogicPtr = movieAppLogicPtr;

    QPixmap bkgnd("Resources/Pictures/background_searchPage.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QPalette pal = ui.listWidget->palette();
    pal.setColor(QPalette::Base, Qt::transparent);
    ui.listWidget->setPalette(pal);

    connect(ui.MenuButton, SIGNAL(clicked()), SLOT(onMenuButtonClicked()));
    connect(ui.HomepageButton, SIGNAL(clicked()), SLOT(onHomepageButtonClicked()));
    connect(ui.LogOutButton, SIGNAL(clicked()), SLOT(onLogOutButtonClicked()));
    connect(ui.WatchedListButton, SIGNAL(clicked()), SLOT(onWatchedListButtonClicked()));
    connect(ui.WishListButton, SIGNAL(clicked()), SLOT(onWishListButtonClicked()));
    connect(ui.MyProfileButton, SIGNAL(clicked()), SLOT(onMyProfileButtonClicked()));
    connect(ui.SearchShowButton, SIGNAL(clicked()), SLOT(onSearchButtonClicked()));
    connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
}

SearchPage::~SearchPage()
{}

void SearchPage::onMenuButtonClicked()
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

void SearchPage::onLogOutButtonClicked()
{
    //std::shared_ptr<MovieAppFE> loginPage = std::make_shared<MovieAppFE>();
    MovieAppFE* loginPage = new MovieAppFE();
    loginPage->show();
    this->hide();
}

void SearchPage::onHomepageButtonClicked()
{
    Homepage* homepage = new Homepage(m_MovieAppLogicPtr);
    homepage->show();
    this->hide();
}

void SearchPage::onWatchedListButtonClicked()
{
    //std::shared_ptr<WatchedList> watchedList = std::make_shared<WatchedList>(m_MovieAppLogicPtr);
    WatchedList* watchedList = new WatchedList(m_MovieAppLogicPtr);
    watchedList->show();
    this->hide();
}

void SearchPage::onWishListButtonClicked()
{
    //std::shared_ptr<WishList> wishList = std::make_shared<WishList>(m_MovieAppLogicPtr);
    WishList* wishList = new WishList(m_MovieAppLogicPtr);
    wishList->show();
    this->hide();
}

void SearchPage::onMyProfileButtonClicked()
{
    //std::shared_ptr<UserProfile> userProfile = std::make_shared<UserProfile>(m_MovieAppLogicPtr);
    UserProfile* userProfile = new UserProfile(m_MovieAppLogicPtr);
    userProfile->show();
    this->hide();
}

void SearchPage::onItemDoubleClicked(QListWidgetItem* lwi)
{
    auto copil = ui.listWidget->currentItem();
    //std::shared_ptr<MoviePage> moviePage = std::make_shared<MoviePage>(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
    MoviePage* moviePage = new MoviePage(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
    moviePage->show();
    this->hide();
}

void SearchPage::onSearchButtonClicked()
{
    auto& storage = Database::GetInstance();
    std::vector<DbShow> shows = MovieAppLogic::SearchShows(ui.searchLineEdit->text().toStdString());
    for (const auto& show : shows)
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
