#include "TicTacToeGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    ITicTacToeGamePtr gamePtr = ITicTacToeGame::Produce();
    QApplication a(argc, argv);
    TicTacToeGUI w(gamePtr);
    w.show();
    return a.exec();
}
