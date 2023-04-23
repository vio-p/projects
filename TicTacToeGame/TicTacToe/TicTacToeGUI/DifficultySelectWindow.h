#pragma once
#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include "ITicTacToeGame.h"

class DifficultySelectWindow : public QDialog
{
public:
	DifficultySelectWindow(ITicTacToeGamePtr gamePtr, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
	ITicTacToeGamePtr m_GamePtr;
	QPushButton m_BtnEasy, m_BtnMedium, m_BtnHard;
	QLabel m_LblTitle;

private slots:
	void OnEasySelect();
	void OnMediumSelect();
	void OnHardSelect();
};

