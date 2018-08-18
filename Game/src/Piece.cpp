#include "Piece.h"
#include "Player.h"
#include "Square.h"
Piece::Piece(Player* player,Square* square):path(2){
    m_player = player;
    PieceSquare = square;
}
Piece::~Piece(){
}

