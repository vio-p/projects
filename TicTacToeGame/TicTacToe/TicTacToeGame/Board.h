#pragma once

#include <vector>

#include "EGameState.h"

class Board
{
private:
	int m_BoardSize;
	std::vector<std::vector<char>> m_BoardState;

	using Position = std::pair<int, int>;
	
private:
	EGameState CheckLine(int lineIndex) const;
	EGameState CheckColumn(int columnIndex) const;
	EGameState CheckMainDiagonal() const;
	EGameState CheckSecondaryDiagonal() const;

public:
	Board(int boardSize = 3);
	Board(const std::vector<std::vector<char>>& boardState);
	~Board() = default;

	std::vector<std::vector<char>> GetBoardState() const;
	EGameState CheckGameState() const;
	std::vector<Position> GetEmptyPositions() const;

	void MarkPosition(const Position& position, char symbol);
};

