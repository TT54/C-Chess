#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "ChessBoard.hpp"
using namespace std;


ChessPiece getPieceFromChar(char fenChar){
    for(int i = 0; i < 12; i++){
        if(piecesFenChar[i] == fenChar) return (ChessPiece) i;
    }
    return NONE;
}

int getPieceId(ChessPiece piece){
    return piecesId[piece];
}

int getUnsignedPieceId(ChessPiece piece){
    return piecesUnsignedId[piece];
}

bool isPieceWhite(ChessPiece piece){
    return piecesColor[piece];
}

char getPieceFenChar(ChessPiece piece){
    return piecesFenChar[piece];
}

int getPieceBeginStandardOffset(ChessPiece piece){
    return piecesBeginStandardOffset[piece];
}

int getPieceEndStandardOffset(ChessPiece piece){
    return piecesEndStandardOffset[piece];
}

bool canPieceAttackBeBlocked(ChessPiece piece){
    return piecesCanAttackBeBlocked[piece];
}

int getPosition(int row, int column){
    return (row << 3) | column;
}

ChessBoard::ChessBoard()
{
    
}

ChessBoard::ChessBoard(string fen)
{
    loadFen(fen);
}

ChessBoard::~ChessBoard()
{
}

void ChessBoard::addPiecePosition(ChessPiece piece, int position){
    if(this->piecesPositions.count(piece) > 0){
        vector<int> positions = this->piecesPositions[piece];
        positions.push_back(position);
        this->piecesPositions[piece] = positions;
    } else{
        vector<int> positions = {position};
        this->piecesPositions[piece] = positions;
    }
    
    int pieceId = getPieceId(piece);
    board[position] = pieceId;

    if(getUnsignedPieceId(piece) == 6){
        if(pieceId == 6){
            whiteKingPosition = position;
        } else if(pieceId == -6){
            blackKingPosition = position;
        }
    }
}

void ChessBoard::printBoard(){
    for(int i = 7; i > -1; i--){
        for(int j = 0; j < 8; j++){
            int p = board[i * 8 + j];
            cout << ((p >= 0) ? " " : "") << p;
            if(j != 7) cout << " |";
        }
        cout << endl;
    }
}

void ChessBoard::loadFen(string fen){
    // Clearing current datas
    piecesPositions.clear();
    for(int i = 0; i < 64; i++){
        board[i] = 0;
    }
    castles = 0;

    // Splitting the fen
    stringstream ss(fen);
    string arg;
    int index = 0;
    while(getline(ss, arg, ' ')){
        if(index == 0){
            stringstream ss2(arg);
            string pos;

            int column = 0;
            int row = 7;
            while(getline(ss2, pos, '/')){
                for(int i = 0; i < pos.length(); ++i){
                    char c = pos[i];
                    if(c >= '0' && c <= '9'){
                        column += c - '0';
                    } else{
                        ChessPiece piece = getPieceFromChar(c);
                        addPiecePosition(piece, getPosition(row, column));
                        column++;
                    }
                }
                column = 0;
                row--;
            }
        }

        index++;
    }
}