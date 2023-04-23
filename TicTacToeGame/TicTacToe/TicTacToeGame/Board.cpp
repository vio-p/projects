#include "Board.h"
#include <stdexcept>

EGameState Board::CheckLine(int lineIndex) const
{
	char symbol = m_BoardState[lineIndex][0];
	if (!symbol)
	{
		return EGameState::Ongoing;
	}
	bool sameSymbol = true;
	for (int column = 1; column < m_BoardSize; column++)
	{
		if (!m_BoardState[lineIndex][column])
		{
			return EGameState::Ongoing;
		}
		if (m_BoardState[lineIndex][column] != symbol)
		{
			sameSymbol = false;
		}
	}
	if (sameSymbol)
	{
		return EGameState::Win;
	}
	return EGameState::None;
}

EGameState Board::CheckColumn(int columnIndex) const
{
	char symbol = m_BoardState[0][columnIndex];
	if (!symbol)
	{
		return EGameState::Ongoing;
	}
	bool sameSymbol = true;
	for (int line = 1; line < m_BoardSize; line++)
	{
		if (!m_BoardState[line][columnIndex])
		{
			return EGameState::Ongoing;
		}
		if (m_BoardState[line][columnIndex] != symbol)
		{
			sameSymbol = false;
		}
	}
	if (sameSymbol)
	{
		return EGameState::Win;
	}
	return EGameState::None;
}

EGameState Board::CheckMainDiagonal() const
{
	char symbol = m_BoardState[0][0];
	if (!symbol)
	{
		return EGameState::Ongoing;
	}
	bool sameSymbol = true;
	for (int line = 1; line < m_BoardSize; line++)
	{
		if (m_BoardState[line][line] != symbol) // column == line for main diagonal
		{
			sameSymbol = false;
		}
	}
	if (sameSymbol)
	{
		return EGameState::Win;
	}
	return EGameState::None;
}

EGameState Board::CheckSecondaryDiagonal() const
{
	char symbol = m_BoardState[0][m_BoardSize - 1];
	if (!symbol)
	{
		return EGameState::Ongoing;
	}
	bool sameSymbol = true;
	for (int line = 1; line < m_BoardSize; line++)
	{
		if (m_BoardState[line][m_BoardSize - line - 1] != symbol) // column == m_BoardSize - line - 1 for secondary diagonal
		{
			sameSymbol = false;
		}
	}
	if (sameSymbol)
	{
		return EGameState::Win;
	}
	return EGameState::None;
}

Board::Board(int boardSize)
{
	m_BoardSize = boardSize;
	m_BoardState.resize(m_BoardSize);
	for (int index = 0; index < m_BoardSize; index++)
	{
		m_BoardState[index].resize(m_BoardSize, 0);
	}
}

Board::Board(const std::vector<std::vector<char>>& boardState)
{
	m_BoardSize = boardState.size();
	m_BoardState = boardState;
}

std::vector<std::vector<char>> Board::GetBoardState() const
{
	return m_BoardState;
}

EGameState Board::CheckGameState() const
{
	if (CheckMainDiagonal() == EGameState::Win)
	{
		return EGameState::Win;
	}
	if (CheckSecondaryDiagonal() == EGameState::Win)
	{
		return EGameState::Win;
	}
	bool isOngoing = false;
	for (int index = 0; index < m_BoardSize; index++)
	{
		if (CheckLine(index) == EGameState::Win)
		{
			return EGameState::Win;
		}
		else if (CheckLine(index) == EGameState::Ongoing)
		{
			isOngoing = true;
		}
		if (CheckColumn(index) == EGameState::Win)
		{
			return EGameState::Win;
		}
		else if (CheckColumn(index) == EGameState::Ongoing)
		{
			isOngoing = true;
		}
	}
	if (isOngoing)
	{
		return EGameState::Ongoing;
	}
	return EGameState::Draw;
}

std::vector<Board::Position> Board::GetEmptyPositions() const
{
	std::vector<std::pair<int, int>> emptyLocations;

	for (int line = 0; line < m_BoardSize; line++)
	{
		for (int column = 0; column < m_BoardSize; column++)
		{
			if (!m_BoardState[line][column])
			{
				emptyLocations.emplace_back(line, column);
			}
		}
	}

	return emptyLocations;
}

void Board::MarkPosition(const Position& position, char symbol)
{
	if (position.first >= m_BoardSize || position.second >= m_BoardSize || position.first < 0 || position.second < 0)
	{
		throw std::exception{ "Invalid position" };
	}
	if (m_BoardState[position.first][position.second] != 0)
	{
		throw std::exception{ "Marked position" };
	}
	m_BoardState[position.first][position.second] = symbol;
}
