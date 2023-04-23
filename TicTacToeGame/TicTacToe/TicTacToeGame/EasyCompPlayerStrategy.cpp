#include "EasyCompPlayerStrategy.h"
#include "Board.h"

#include <random>

std::pair<int, int> EasyCompPlayerStrategy::PickPosition(const std::vector<std::vector<char>>& boardState)
{
	Board board{ boardState };
	std::vector<std::pair<int, int>> emptyLocations = board.GetEmptyPositions();

	if (emptyLocations.empty())
	{
		throw std::exception{ "No place to pick" };
	}

	std::random_device rd;
	int last = emptyLocations.size() - 1;
	std::uniform_int_distribution<int> dist(0, last);

	return emptyLocations[dist(rd)];
}