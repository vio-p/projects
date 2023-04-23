#pragma once

#include <memory>

#include "ITicTacToeGame.h"
#include "Board.h"
#include "EasyCompPlayerStrategy.h"

class TicTacToeGame : public ITicTacToeGame
{
private:
	std::vector<ITicTacToeListener*> m_Listeners;

	Board m_Board;
	std::shared_ptr<ICompPlayerStrategy> m_CompPlayerStrategy;

public:
	TicTacToeGame();

	void AddListener(ITicTacToeListener* listener) override;
	void RemoveListener(ITicTacToeListener* listener) override;
	void SetCompPlayerStrategy(const std::shared_ptr<ICompPlayerStrategy>& compPlayerStrategy) override;
	void Reset() override;
	void MakeMove(int x, int y) override;

private:
	void NotifyBoardChanged(const std::vector<std::vector<char>>& boardState) const;
	void NotifyGameOver(EGameState gameState) const;
	void NotifyExceptionRaised(const std::exception& exception) const;
};

