#include "TicTacToeGUI.h"

#include <QGridLayout>
#include "DifficultySelectWindow.h"

TicTacToeGUI::TicTacToeGUI(const ITicTacToeGamePtr& gamePointer)
	: QMainWindow(nullptr)
{
	ui.setupUi(this);

	m_ITicTacToeGamePtr = gamePointer;
	m_ITicTacToeGamePtr->AddListener(this);

	PromptUserDifficulty();

	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(92, 44, 148));

	// Set the background color of the main widget
	setAutoFillBackground(true);
	setPalette(pal);

	int buttonWidth = 120;
	int buttonHeight = 80;
	int leftOffset = 60;
	int topOffset = 60;
	int buttonGap = 20;

	m_Buttons.resize(k_BoardSize);
	for (int i = 0; i < k_BoardSize; i++)
	{
		m_Buttons[i].resize(k_BoardSize);
		for (int j = 0; j < k_BoardSize; j++)
		{
			ButtonTicTacToe* button = new ButtonTicTacToe({ i,j }, this);
			button->setGeometry(leftOffset + (buttonWidth + buttonGap) * j, topOffset + (buttonHeight + buttonGap) * i, buttonWidth, buttonHeight);
			button->setFont(QFont("Arial", 24, QFont::Bold));
			connect(button, &ButtonTicTacToe::tttClicked, this, &TicTacToeGUI::OnTTTButtonClicked);
			m_Buttons[i][j] = button;
		}
	}
}

TicTacToeGUI::~TicTacToeGUI()
{
	m_ITicTacToeGamePtr->RemoveListener(this);
	for (auto& line : m_Buttons)
	{
		for (auto& button : line)
		{
			delete button;
		}
	}
}

void TicTacToeGUI::OnBoardChanged(const std::vector<std::vector<char>>& boardState)
{
	for (int i = 0; i < boardState.size(); i++)
	{
		for (int j = 0; j < boardState.size(); j++)
		{
			QChar symbol = boardState[i][j];
			QPushButton* button = m_Buttons[i][j];
			button->setText(QString(symbol));
		}
	}
}

void TicTacToeGUI::OnExceptionRaised(const std::exception& exception)
{
	// Initialize message box and set default title and icon
	QMessageBox msgBox;
	msgBox.setWindowTitle("Error");
	msgBox.setIcon(QMessageBox::Warning);

	// Set text and informative text
	msgBox.setText("Oops! An error occurred:");
	msgBox.setInformativeText(exception.what());

	// Set button
	msgBox.addButton(QMessageBox::Ok);

	// Set style sheet for message box
	QString styleSheet = "QMessageBox {background-color: white;}"
		"QMessageBox QLabel {color: black bold;}"
		"QMessageBox QPushButton {background-color: #0074D9; color: white; font-size:16px; font-weight: bold;}"
		"QMessageBox QPushButton:hover {background-color: rgb(200, 200, 200);}";
	msgBox.setStyleSheet(styleSheet);

	// Display message box and wait for response
	msgBox.exec();
}

void TicTacToeGUI::OnGameOver(EGameState gameState)
{
	// Initialize message box and set default title and icon
	QMessageBox msgBox;
	msgBox.setWindowTitle("Game over");
	msgBox.setIcon(QMessageBox::Information);

	// Set message and button based on game state
	switch (gameState)
	{
	case EGameState::Win:
		msgBox.setText("Congratulations! You won!");
		msgBox.addButton(QMessageBox::Ok);
		break;

	case EGameState::Loss:
		msgBox.setText("Sorry, you lost. Better luck next time!");
		msgBox.addButton(QMessageBox::Ok);
		break;

	case EGameState::Draw:
		msgBox.setText("It's a draw! Nobody wins.");
		msgBox.addButton(QMessageBox::Ok);
		break;

	default:
		msgBox.setText("Unknown game state.");
		msgBox.addButton(QMessageBox::Ok);
		break;
	}

	QString styleSheet = "QLabel{ color: black; font-size: 16px; } "
		"QPushButton{ background-color: #0074D9; color: white; font-size: 16px; font-weight: bold; } "
		"QPushButton:hover{ background-color: #0063AF; }";
	msgBox.setStyleSheet(styleSheet);

	// Display message box and wait for response before exiting
	msgBox.exec();

	// Clear board
	m_ITicTacToeGamePtr->Reset();

	// Ask for difficulty
	PromptUserDifficulty();
}

void TicTacToeGUI::OnTTTButtonClicked(const std::pair<int, int>& position)
{
	m_ITicTacToeGamePtr->MakeMove(position.second, position.first);
}

void TicTacToeGUI::PromptUserDifficulty()
{
	auto dificultySelectWindow = new DifficultySelectWindow(m_ITicTacToeGamePtr);
	dificultySelectWindow->exec();
}
