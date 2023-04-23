#include "MoviePage.h"

MoviePage::MoviePage(std::shared_ptr<MovieAppLogic> movieAppLogicPtr, int showId, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	m_MovieAppLogicPtr = movieAppLogicPtr;
	m_ShowId = showId;
	m_Show = MovieAppLogic::GetShow(showId);
	m_ShowRating = 0;

	QPixmap bkgnd("Resources/Pictures/background_moviePage.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	InitCompStyleSheets();
	std::string title = m_Show.GetTitle() + " (" + std::to_string(m_Show.GetReleaseYear()) + ")";
	ui.label_Title->setText(QString::fromStdString(title));
	ui.label_ShowType->setText(QString::fromStdString(m_Show.GetType()));
	std::string score = "Score: ";
	if (m_Show.GetNumberOfRatings() > 5)
	{
		score += std::to_string(m_Show.GetStars());
	}
	ui.label_Score->setText(QString::fromStdString(score));
	std::string rating = "Rating: ";
	rating += m_Show.GetRating();
	ui.label_Rating->setText(QString::fromStdString(rating));
	std::string duration = "Duration: ";
	duration += m_Show.GetDuration();
	ui.label_Duration->setText(QString::fromStdString(duration));
	std::string cast = "Cast: ";
	cast += m_Show.GetActors();
	ui.label_Cast->setText(QString::fromStdString(cast));
	std::string directors = "Directed by: ";
	directors += m_Show.GetDirectors();
	ui.label_Directors->setText(QString::fromStdString(directors));
	std::string categories = "Listen in: ";
	categories += m_Show.GetCategories();
	ui.label_Categories->setText(QString::fromStdString(categories));
	std::string countries = "Countries: ";
	countries += m_Show.GetCountries();
	ui.label_Countries->setText(QString::fromStdString(countries));
	std::string description = "Description: ";
	description += m_Show.GetDescription();
	ui.label_Description->setText(QString::fromStdString(description));

	if (m_MovieAppLogicPtr->IsAlreadyInWatchedList(m_ShowId))
	{
		ui.label_LastWatched->setText("Last watched on:" + QString::fromStdString(m_MovieAppLogicPtr->GetDateLastWatched(m_ShowId)));
	}
	else
	{
		ui.label_LastWatched->setText("");
	}

	AddSimilarShows();

	connect(ui.RateButton, SIGNAL(clicked()), SLOT(onRateButtonClicked()));
	connect(ui.AddWatchedButton, SIGNAL(clicked()), SLOT(onAddWatchedButtonClicked()));
	connect(ui.AddWishButton, SIGNAL(clicked()), SLOT(onAddWishButtonClicked()));
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
	connect(ui.HomepageButton, SIGNAL(clicked()), SLOT(onHomepageButtonClicked()));
}

MoviePage::~MoviePage()
{}

void MoviePage::InitCompStyleSheets()
{
	ui.label_Title->setStyleSheet("color: rgb(255, 255, 255);font: 700 14pt \"Segoe UI\";");
	ui.label_ShowType->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Score->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Rating->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Duration->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Cast->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Directors->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Categories->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Countries->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_Description->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_SimilarShows->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");
	ui.label_LastWatched->setStyleSheet("color: rgb(2, 41, 58);font: 700 9pt \"Segoe UI\";");

	// widget list palette
	QPalette pal = ui.listWidget->palette();
	pal.setColor(QPalette::Base, Qt::transparent);
	ui.listWidget->setPalette(pal);
}

void MoviePage::AddSimilarShows()
{
	auto similarShows = MovieAppLogic::GetSimilarShows(m_ShowId);
	for (const auto& show : similarShows)
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

void MoviePage::onRateButtonClicked()
{
	if (ui.RateLineEdit->text().isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Type your rating into the textbox");
		return;
	}
	bool isValid;
	int rating = ui.RateLineEdit->text().toInt(&isValid);
	if (rating < 0 || rating > 5 || !isValid)
	{
		QMessageBox::warning(this, "Warning", "You should rate the show out of 5 stars.");
		return;
	}
	m_ShowRating = rating;
}

void MoviePage::onAddWatchedButtonClicked()
{
	if (m_ShowRating == 0)
	{
		QMessageBox::warning(this, "Warning", "Rating the show helps us give better recommendations.\nRate the show before marking it as watched.");
		return;
	}
	std::string message = m_MovieAppLogicPtr->AddShowToWatchedList(m_ShowId, m_ShowRating);
	QMessageBox::information(this, "Information", QString::fromStdString(message));
}

void MoviePage::onAddWishButtonClicked()
{
	if (m_MovieAppLogicPtr->IsAlreadyInWishList(m_ShowId))
	{
		std::string dateAdded = m_MovieAppLogicPtr->GetDateAddedToWishList(m_ShowId);
		QString message = "This show is in your wishlist since " + QString::fromStdString(dateAdded);
		QMessageBox::information(this, "Information", message);
		return;
	}
	m_MovieAppLogicPtr->AddShowToWishList(m_ShowId);
}

void MoviePage::onItemDoubleClicked(QListWidgetItem* lwi)
{
	auto copil = ui.listWidget->currentItem();
	//std::shared_ptr<MoviePage> moviePage = std::make_shared<MoviePage>(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	MoviePage* moviePage = new MoviePage(m_MovieAppLogicPtr, copil->data(Qt::UserRole).toInt());
	moviePage->show();
	this->hide();
}

void MoviePage::onHomepageButtonClicked()
{
	Homepage* homepage = new Homepage(m_MovieAppLogicPtr);
	homepage->show();
	this->hide();
}
