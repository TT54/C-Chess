#include <iostream>
#include "ChessBoard.hpp"
using namespace std;

int main(){
    ChessBoard board = ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    board.printBoard();
}