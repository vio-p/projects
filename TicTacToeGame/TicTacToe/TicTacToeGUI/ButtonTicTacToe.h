#pragma once
#include <QPushButton>

class ButtonTicTacToe : public QPushButton
{
	Q_OBJECT

public:
	ButtonTicTacToe(const std::pair<int, int>& position, QWidget* parent = nullptr);
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void tttClicked(const std::pair<int, int>& position);

private:
	std::pair<int, int> m_Position;
};

