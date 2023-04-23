#include "TicTacToeConsole.h"

int main()
{
	ITicTacToeGamePtr gamePtr = ITicTacToeGame::Produce();
	TicTacToeConsole ticTacToeConsole(gamePtr);
	ticTacToeConsole.Run();
}