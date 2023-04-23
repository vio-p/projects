#include "DifficultySelectWindow.h"

DifficultySelectWindow::DifficultySelectWindow(ITicTacToeGamePtr gamePtr, QWidget* parent, Qt::WindowFlags f):
	QDialog(parent, f), m_GamePtr(gamePtr),
	m_BtnEasy("Easy", this), m_BtnMedium("Medium", this), m_BtnHard("Hard", this),
	m_LblTitle("Select the preferred difficulty: ", this)
{
	setWindowFlag(Qt::WindowCloseButtonHint, false);
	setFixedSize(340, 120);

	m_BtnEasy.setGeometry(40, 50, 60, 40);
	m_BtnMedium.setGeometry(140, 50, 60, 40);
	m_BtnHard.setGeometry(240, 50, 60, 40);

	m_LblTitle.setGeometry(0, 10, 340, 30);
	m_LblTitle.setAlignment(Qt::AlignCenter);

	connect(&m_BtnEasy, &QPushButton::released, this, &DifficultySelectWindow::OnEasySelect);
	connect(&m_BtnMedium, &QPushButton::released, this, &DifficultySelectWindow::OnMediumSelect);
	connect(&m_BtnHard, &QPushButton::released, this, &DifficultySelectWindow::OnHardSelect);
}

void DifficultySelectWindow::OnEasySelect()
{
	m_GamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Easy));
	close();
}

void DifficultySelectWindow::OnMediumSelect()
{
	m_GamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Medium));
	close();
}

void DifficultySelectWindow::OnHardSelect()
{
	m_GamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Hard));
	close();
}

