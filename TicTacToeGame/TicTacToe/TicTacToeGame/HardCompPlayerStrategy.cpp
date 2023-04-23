#include "HardCompPlayerStrategy.h"

#include <random>

std::pair<int, int> HardCompPlayerStrategy::PickPosition(const std::vector<std::vector<char>>& boardState)
{
	if (Board(boardState).GetEmptyPositions().empty())
	{
		throw std::exception{ "No place to pick" };
	}
	return Minimax(Board{ boardState }, 1).first;
}

std::pair<std::pair<int, int>, int> HardCompPlayerStrategy::Minimax(const Board& board, int level) const
{
	const auto emptyLocations = board.GetEmptyPositions();
	const bool isCompPlayer = level % 2;

	const int kWinScore = 5;
	const int kDrawScore = 0;

	std::pair<int, int> bestLocation{ -1,-1 };
	int bestValue = -10;

	for (const auto& option : emptyLocations)
	{
		int currentOptionValue = 0;
		auto currentBoard = board;
		currentBoard.MarkPosition(option, isCompPlayer ? 'O' : 'X');
		auto state = currentBoard.CheckGameState();

		if (state == EGameState::Draw)
		{
			currentOptionValue = kDrawScore;
		}
		else if (state == EGameState::Win)
		{
			currentOptionValue = kWinScore;
		}
		else
		{
			currentOptionValue = -Minimax(currentBoard, level + 1).second;
		}

		if (currentOptionValue > bestValue)
		{
			bestValue = currentOptionValue;
			bestLocation = option;

			if (bestValue == kWinScore)
				break;
		}
	}

	return { bestLocation, bestValue };
}
