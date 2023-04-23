#pragma once

#include "ITicTacToeGame.h"

class TicTacToeConsole : public ITicTacToeListener
{
	ITicTacToeGamePtr m_ITicTacToeGamePtr;

	bool m_GameIsRunning;

public:
	TicTacToeConsole(const ITicTacToeGamePtr& gamePointer);
	~TicTacToeConsole() override;

	void OnBoardChanged(const std::vector<std::vector<char>>& boardState) override;
	void OnGameOver(EGameState gameState) override;
	void OnExceptionRaised(const std::exception& exception) override;

	void Run();
};


