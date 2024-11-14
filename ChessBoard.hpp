#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

enum ChessPiece{

    NONE = -1,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_ROOK,
    BLACK_BISHOP,
    BLACK_KNIGHT,
    BLACK_PAWN,
    WHITE_PAWN,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_ROOK,
    WHITE_QUEEN,
    WHITE_KING

};

const int piecesId[] = {-6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6};
const int piecesUnsignedId[] = {6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6};
const bool piecesColor[] = {false, false, false, false, false, false, true, true, true, true, true, true};
const char piecesFenChar[] = {'k', 'q', 'r', 'b', 'n', 'p', 'P', 'N', 'B', 'R', 'Q', 'K'};
const int piecesBeginStandardOffset[] = {-1, 0, 0, 4, -1, -1, -1, -1, 4, 0, 0, -1};
const int piecesEndStandardOffset[] = {-1, 7, 3, 7, -1, -1, -1, -1, 7, 3, 7, -1};
const bool piecesCanAttackBeBlocked[] = {false, true, true, true, false, false, false, false, true, true, true, false};

class ChessBoard
{
private:
    bool whiteToPlay;
    int board[64];
    int castles;
    int enPassant;
    
    unordered_map<ChessPiece, vector<int>> piecesPositions;
    vector<int> squaresAttackers[64];
    int pins[64];
    int checks[64];
    
    int whiteKingPosition;
    int blackKingPosition;

    void loadFen(string fen);
    void addPiecePosition(ChessPiece piece, int position);

public:
    ChessBoard();
    ChessBoard(string fen);
    ~ChessBoard();
    
    void printBoard();

};