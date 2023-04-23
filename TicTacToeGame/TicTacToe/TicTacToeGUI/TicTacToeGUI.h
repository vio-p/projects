#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>

#include "ui_TicTacToeGUI.h"
#include "ITicTacToeGame.h"
#include "ButtonTicTacToe.h"

class TicTacToeGUI : public QMainWindow, public ITicTacToeListener
{
    Q_OBJECT

public:
    TicTacToeGUI(const ITicTacToeGamePtr& gamePointer);
    ~TicTacToeGUI() override;

    void OnBoardChanged(const std::vector<std::vector<char>>& boardState) override;
    void OnExceptionRaised(const std::exception& exception) override;
    void OnGameOver(EGameState gameState) override;

    void OnTTTButtonClicked(const std::pair<int, int>& position);
    void PromptUserDifficulty();

private:
    Ui::TicTacToeGUIClass ui;
    ITicTacToeGamePtr m_ITicTacToeGamePtr;
    std::vector<std::vector<ButtonTicTacToe*>> m_Buttons;
    const int k_BoardSize = 3;
};
