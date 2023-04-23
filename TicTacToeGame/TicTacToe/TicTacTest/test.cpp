#include <queue>

#include "HardCompPlayerStrategy.h"
#include "pch.h"
#include "TicTacToeGame.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

// ===================
// EasyCompPlayerStrategy Tests
// ===================

TEST(TestEasyComputerPlayer, CheckValid) {
	EasyCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {'X', '0', 'X'}, {0, 'X', '0'}, {'0', '0', 'X'} };
	std::pair<int, int> result = { 1,0 };
	EXPECT_EQ(compPlayer.PickPosition(matrix), result);
}

TEST(TestEasyComputerPlayer, CheckInvalid) {
	EasyCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {'X', '0', 'X'}, {'X', 'X', '0'}, {'0', '0', 'X'} };
	EXPECT_ANY_THROW(compPlayer.PickPosition(matrix));
}

// ===================
// HardCompPlayerStrategy Tests
// ===================

TEST(TestHardComputerPlayer, CheckValid) {
	HardCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {'X', '0', 'X'}, {0, 'X', '0'}, {'0', '0', 'X'} };
	std::pair<int, int> result = { 1,0 };
	EXPECT_EQ(compPlayer.PickPosition(matrix), result);
}

TEST(TestHardComputerPlayer, CheckInvalid) {
	HardCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {'X', '0', 'X'}, {'X', 'X', '0'}, {'0', '0', 'X'} };
	EXPECT_ANY_THROW(compPlayer.PickPosition(matrix));
}

TEST(TestHardComputerPlayer, CheckBlock) {
	HardCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {0, 0, 0}, {0, '0', 0}, {0, 'X', 'X'}};
	std::pair<int, int> result = { 2,0 };
	EXPECT_EQ(compPlayer.PickPosition(matrix), result);
}

TEST(TestHardComputerPlayer, CheckWin) {
	HardCompPlayerStrategy compPlayer;

	std::vector<std::vector<char>> matrix = { {'X', 'X', '0'}, {'X', '0', 0}, {0, 0, 'X'}};
	std::pair<int, int> result = { 2,0 };
	EXPECT_EQ(compPlayer.PickPosition(matrix), result);
}

// ===================
// Board Tests
// ===================

TEST(TestBoard, CheckGetBoardEmptyStart) {
	Board board;

	std::vector<std::vector<char>> matrix = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	EXPECT_EQ(board.GetBoardState(), matrix);

	EXPECT_EQ(board.CheckGameState(), EGameState::Ongoing);
}

TEST(TestBoard, CheckMarkPositionAndGetBoard) {
	Board board;
	board.MarkPosition({ 0,2 }, '8');
	board.MarkPosition({ 0,1 }, '3');
	board.MarkPosition({ 2,1 }, '4');
	board.MarkPosition({ 0,0 }, '0');
	board.MarkPosition({ 2,0 }, '5');
	board.MarkPosition({ 1,0 }, '2');
	board.MarkPosition({ 1,1 }, '1');
	board.MarkPosition({ 1,2 }, '6');
	board.MarkPosition({ 2,2 }, '9');

	std::vector<std::vector<char>> matrix = { {'0', '3', '8'}, {'2', '1', '6'}, {'5', '4', '9'} };
	EXPECT_EQ(board.GetBoardState(), matrix);
}

TEST(TestBoard, CheckMarkPositionOccupied) {
	Board board;
	board.MarkPosition({ 0,0 }, '3');
	board.MarkPosition({ 0,1 }, '1');
	EXPECT_ANY_THROW(board.MarkPosition({ 0,0 }, '9'));
}

TEST(TestBoard, CheckMarkPositionOutsideRange) {
	Board board;
	board.MarkPosition({ 0,0 }, 'X');
	EXPECT_ANY_THROW(board.MarkPosition({ -1,2 }, 'X'));
	EXPECT_ANY_THROW(board.MarkPosition({ 2,3 }, '0'));
}

TEST(TestBoard, CheckState) {
	Board board;
	board.MarkPosition({ 0,0 }, 'X');
	EXPECT_EQ(board.CheckGameState(), EGameState::Ongoing);

	Board board2;
	board2.MarkPosition({ 0,0 }, 'X');
	board2.MarkPosition({ 0,1 }, 'X');
	board2.MarkPosition({ 0,2 }, 'X');
	EXPECT_EQ(board2.CheckGameState(), EGameState::Win);

	Board board3;
	board3.MarkPosition({ 0,0 }, 'X');
	board3.MarkPosition({ 0,1 }, '0');
	board3.MarkPosition({ 0,2 }, 'X');
	board3.MarkPosition({ 1,0 }, '0');
	board3.MarkPosition({ 1,1 }, 'X');
	board3.MarkPosition({ 1,2 }, '0');
	board3.MarkPosition({ 2,0 }, '0');
	board3.MarkPosition({ 2,1 }, 'X');
	board3.MarkPosition({ 2,2 }, '0');
	EXPECT_EQ(board3.CheckGameState(), EGameState::Draw);
}

TEST(TestBoard, CheckWin) {
	Board board;
	board.MarkPosition({ 2,0 }, 'X');
	board.MarkPosition({ 2,1 }, 'X');
	board.MarkPosition({ 2,2 }, 'X');
	EXPECT_EQ(board.CheckGameState(), EGameState::Win);

	Board board2;
	board2.MarkPosition({ 0,0 }, 'X');
	board2.MarkPosition({ 1,0 }, 'X');
	board2.MarkPosition({ 2,0 }, 'X');
	EXPECT_EQ(board2.CheckGameState(), EGameState::Win);

	Board board3;
	board3.MarkPosition({ 0,0 }, 'X');
	board3.MarkPosition({ 1,1 }, 'X');
	board3.MarkPosition({ 2,2 }, 'X');
	EXPECT_EQ(board3.CheckGameState(), EGameState::Win);

	Board board4;
	board4.MarkPosition({ 0,2 }, 'X');
	board4.MarkPosition({ 1,1 }, 'X');
	board4.MarkPosition({ 2,0 }, 'X');
	EXPECT_EQ(board4.CheckGameState(), EGameState::Win);
}

// ===================
// TicTacToeGame Tests
// ===================

using namespace testing;

class DeterministicCompPlayerStrategy : public ICompPlayerStrategy
{
private:
	std::queue<std::pair<int, int>> m_PredefinedMoves;

public:
	DeterministicCompPlayerStrategy(const std::vector<std::pair<int, int>>& predefinedMoves)
	{
		for (const auto& e : predefinedMoves)
			m_PredefinedMoves.push(e);
	}

	std::pair<int, int> PickPosition(const std::vector<std::vector<char>>& boardState) override
	{
		auto current = m_PredefinedMoves.front();
		m_PredefinedMoves.pop();
		return current;
	}
};

class MockTicTacToeListener : public ITicTacToeListener
{
public:
	MOCK_METHOD(void, OnBoardChanged, (const std::vector<std::vector<char>>&), (override));
	MOCK_METHOD(void, OnGameOver, (EGameState), (override));
	MOCK_METHOD(void, OnExceptionRaised, (const std::exception&), (override));
};

TEST(TestTicTacToeGame, OnBoardChanged)
{
	TicTacToeGame game;
	auto deterministicStrategy = std::make_shared<DeterministicCompPlayerStrategy>(std::vector<std::pair<int, int>>{ {1, 1}});
	game.SetCompPlayerStrategy(deterministicStrategy);

	MockTicTacToeListener listener;
	game.AddListener(&listener);

	// Expectations for the listener
	std::vector<std::vector<char>> board = { { 'X', 0, 0 }, { 0, 0, 0}, {0, 0, 0} };
	EXPECT_CALL(listener, OnBoardChanged(board)).Times(1);
	board[1][1] = 'O';
	EXPECT_CALL(listener, OnBoardChanged(board)).Times(1);

	game.MakeMove(0, 0);

	// Verify the expectations
	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveListener(&listener);
}

TEST(TestTicTacToeGame, OnExceptionRaisedOccupied)
{
	TicTacToeGame game;
	auto deterministicStrategy = std::make_shared<DeterministicCompPlayerStrategy>(std::vector<std::pair<int, int>>{ {1, 1}, { 2,2 }});
	game.SetCompPlayerStrategy(deterministicStrategy);

	MockTicTacToeListener listener;
	game.AddListener(&listener);

	// Expectations for the listener
	EXPECT_CALL(listener, OnExceptionRaised).Times(1);
	EXPECT_CALL(listener, OnBoardChanged).Times(AnyNumber());

	game.MakeMove(0, 0);
	game.MakeMove(0, 0);

	// Verify the expectations
	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveListener(&listener);
}

TEST(TestTicTacToeGame, OnExceptionRaisedInvalid)
{
	TicTacToeGame game;

	MockTicTacToeListener listener;
	game.AddListener(&listener);

	// Expectations for the listener
	EXPECT_CALL(listener, OnExceptionRaised).Times(2);

	game.MakeMove(-1, 2);
	game.MakeMove(1, 7);

	// Verify the expectations
	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveListener(&listener);
}

TEST(TestTicTacToeGame, OnGameOver)
{
	TicTacToeGame game;
	auto deterministicStrategy = std::make_shared<DeterministicCompPlayerStrategy>(std::vector<std::pair<int, int>>{ {0, 1}, { 1,1 }, { 2,1 }});
	game.SetCompPlayerStrategy(deterministicStrategy);

	MockTicTacToeListener listener;
	game.AddListener(&listener);

	// Expectations for the listener
	EXPECT_CALL(listener, OnGameOver).Times(1);
	EXPECT_CALL(listener, OnBoardChanged).Times(5);

	game.MakeMove(0, 0);
	game.MakeMove(0, 1);
	game.MakeMove(0, 2);

	// Verify the expectations
	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveListener(&listener);
}

TEST(TestTicTacToeGame, Reset)
{
	TicTacToeGame game;

	MockTicTacToeListener listener;
	game.AddListener(&listener);

	// Expectations for the listener
	std::vector<std::vector<char>> board = { { 0, 0, 0 }, { 0, 0, 0}, {0, 0, 0} };
	EXPECT_CALL(listener, OnBoardChanged(board));

	game.Reset();

	// Verify the expectations
	Mock::VerifyAndClearExpectations(&listener);
	game.RemoveListener(&listener);
}