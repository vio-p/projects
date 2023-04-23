#include "UserPreferences.h"

UserPreferences::UserPreferences(int newUserId, QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QPixmap bkgnd("Resources/Pictures/background_preferences.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	InitCompStyleSheets();
	connect(ui.pushButton, SIGNAL(clicked()), SLOT(onSubmitButtonClicked()));
	m_NewUserId = newUserId;
}

UserPreferences::~UserPreferences()
{}

void UserPreferences::InitCompStyleSheets()
{
	ui.label->setStyleSheet("color: rgb(255, 255, 255);font: 700 13pt \"Segoe UI\";");
	ui.checkBox_1->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_2->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_3->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_4->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_5->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_6->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_7->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_8->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
	ui.checkBox_9->setStyleSheet("color: rgb(255, 255, 255);font: 700 12pt \"Segoe UI\";");
}

void UserPreferences::onSubmitButtonClicked()
{
	std::vector<std::string> selectedCategories;
	if (ui.checkBox_1->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_1->text().toStdString());
	}
	if (ui.checkBox_2->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_2->text().toStdString());
	}
	if (ui.checkBox_3->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_3->text().toStdString());
	}
	if (ui.checkBox_4->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_4->text().toStdString());
	}
	if (ui.checkBox_5->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_5->text().toStdString());
	}
	if (ui.checkBox_6->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_6->text().toStdString());
	}
	if (ui.checkBox_7->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_7->text().toStdString());
	}
	if (ui.checkBox_8->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_8->text().toStdString());
	}
	if (ui.checkBox_9->isChecked())
	{
		selectedCategories.push_back(ui.checkBox_9->text().toStdString());
	}
	MovieAppLogic::AddPreferredCategoriesForUser(m_NewUserId, selectedCategories);
	MovieAppFE* loginWindow = new MovieAppFE();
	loginWindow->show();
	this->hide();
}