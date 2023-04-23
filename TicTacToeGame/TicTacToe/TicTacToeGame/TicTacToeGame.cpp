#include "TicTacToeGame.h"

#include "HardCompPlayerStrategy.h"
#include "MediumCompPlayerStrategy.h"

ITicTacToeGamePtr ITicTacToeGame::Produce()
{
	return std::make_shared<TicTacToeGame>();
}

TicTacToeGame::TicTacToeGame()
{
	m_CompPlayerStrategy = std::make_shared<EasyCompPlayerStrategy>();
}

void TicTacToeGame::AddListener(ITicTacToeListener* listener)
{
	m_Listeners.push_back(listener);
}

void TicTacToeGame::RemoveListener(ITicTacToeListener* listener)
{
	for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
	{
		if (*it == listener)
		{
			m_Listeners.erase(it);
			break;
		}
	}
}

void TicTacToeGame::SetCompPlayerStrategy(const std::shared_ptr<ICompPlayerStrategy>& compPlayerStrategy)
{
	m_CompPlayerStrategy = compPlayerStrategy;
}

void TicTacToeGame::Reset()
{
	m_Board = Board{};
	NotifyBoardChanged(m_Board.GetBoardState());
}

void TicTacToeGame::MakeMove(int x, int y)
{
	std::pair<int, int> position = { y, x };
	const char playerSymbol = 'X';
	const char opponentSymbol = 'O';

	try
	{
		m_Board.MarkPosition(position, playerSymbol);
	}
	catch (const std::exception& exception)
	{
		NotifyExceptionRaised(exception);
		return;
	}

	NotifyBoardChanged(m_Board.GetBoardState());

	auto gameState = m_Board.CheckGameState();
	if (gameState != EGameState::Ongoing)
	{
		if (gameState == EGameState::Win)
			NotifyGameOver(EGameState::Win);

		if (gameState == EGameState::Draw)
			NotifyGameOver(EGameState::Draw);

		return;
	}

	m_Board.MarkPosition(m_CompPlayerStrategy->PickPosition(m_Board.GetBoardState()), opponentSymbol);
	NotifyBoardChanged(m_Board.GetBoardState());

	gameState = m_Board.CheckGameState();
	if (gameState != EGameState::Ongoing)
	{
		if (gameState == EGameState::Win)
			NotifyGameOver(EGameState::Loss);

		if (gameState == EGameState::Draw)
			NotifyGameOver(EGameState::Draw);
	}
}

void TicTacToeGame::NotifyBoardChanged(const std::vector<std::vector<char>>& boardState) const
{
	for (const auto listener : m_Listeners)
	{
		listener->OnBoardChanged(boardState);
	}
}

void TicTacToeGame::NotifyGameOver(EGameState gameState) const
{
	for (const auto listener : m_Listeners)
	{
		listener->OnGameOver(gameState);
	}
}

void TicTacToeGame::NotifyExceptionRaised(const std::exception& exception) const
{
	for (const auto listener : m_Listeners)
	{
		listener->OnExceptionRaised(exception);
	}
}

