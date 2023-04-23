#include "TicTacToeConsole.h"

#include <iostream>
#include <string>

TicTacToeConsole::TicTacToeConsole(const ITicTacToeGamePtr& gamePointer)
{
	m_ITicTacToeGamePtr = gamePointer;
	m_ITicTacToeGamePtr->AddListener(this);
	m_GameIsRunning = false;
}

TicTacToeConsole::~TicTacToeConsole()
{
	m_ITicTacToeGamePtr->RemoveListener(this);
}

void TicTacToeConsole::OnBoardChanged(const std::vector<std::vector<char>>& boardState)
{
	// print the current board state
	std::cout << std::endl;
	const int boardSize = boardState.size();
	for (int i = 0; i < boardSize; i++)
	{
		std::cout << " ";
		for (int j = 0; j < boardSize; j++)
		{
			if (boardState[i][j] != 0)
			{
				std::cout << boardState[i][j];
			}
			else
			{
				std::cout << " ";
			}
			std::cout << " ";
			if (j != boardSize - 1)
			{
				std::cout << "|";
			}
			std::cout << " ";
		}
		if (i < boardSize - 1)
		{
			std::cout << "\n---+---+---\n";
		}
		else
		{
			std::cout << "\n\n";
		}
	}
}

void TicTacToeConsole::OnGameOver(EGameState gameState)
{
	switch (gameState)
	{
	case EGameState::Win:
		std::cout << "Congratulations! You won!";
		break;
	case EGameState::Loss:
		std::cout << "Sorry, you lost. Better luck next time!";
		break;
	case EGameState::Draw:
		std::cout << "It's a draw! Nobody wins.";
		break;
	default:
		std::cout << "Unknown game state.";
		break;
	}
	std::cout << std::endl << std::endl;
	m_GameIsRunning = false;
}

void TicTacToeConsole::OnExceptionRaised(const std::exception& exception)
{
	std::cout << "Oops! An error occurred: " << exception.what() << std::endl << std::endl;
}

void TicTacToeConsole::Run()
{
	std::cout << "                          --- TIC TAC TOE GAME ---\n";
	while (true)
	{
		std::cout << "Choose an option:\n";
		std::cout << "p - Play game\n";
		std::cout << "e - Change game difficulty to EASY (default)\n";
		std::cout << "m - Change game difficulty to MEDIUM\n";
		std::cout << "h - Change game difficulty to HARD\n";
		std::cout << "q - Quit the application\n\n";
		std::cout << "Option: ";
		std::string option;
		std::cin >> option;
		if (option.size() > 1)
		{
			option[0] = 'x';
		}
		switch (option[0])
		{
		case 'p':
		{
			m_GameIsRunning = true;
			m_ITicTacToeGamePtr->Reset();
			while (m_GameIsRunning)
			{
				std::string x, y;
				std::cout << "Pick a position: ";
				std::cin >> y >> x;
				try
				{
					m_ITicTacToeGamePtr->MakeMove(std::stoi(x), std::stoi(y));
				}
				catch (const std::exception&)
				{
					std::cout << "The position should be a pair of integers!\n\n";
				}
			}
			break;
		}
		case 'e':
			m_ITicTacToeGamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Easy));
			std::cout << "The difficulty was set to EASY\n\n";
			break;
		case 'm':
			m_ITicTacToeGamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Medium));
			std::cout << "The difficulty was set to MEDIUM\n\n";
			break;
		case 'h':
			m_ITicTacToeGamePtr->SetCompPlayerStrategy(ICompPlayerStrategy::Produce(EStrategyType::Hard));
			std::cout << "The difficulty was set to HARD\n\n";
			break;
		case 'q':
			exit(0);
			break;
		default:
			std::cout << "Choose a valid option!\n\n";
			break;
		}
	}
}
