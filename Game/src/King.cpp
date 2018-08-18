#include "King.h"
#include <stdlib.h>
#include "Player.h"
#include "Game.h"
#include "Board.h"
King::King(Player* player,Square* square):Piece(player,square)
{
    m_type = KING;
}

King::~King(){
}

bool King::canCapture(Piece* capture_piece)
{
    if(isValidPath(capture_piece->PieceSquare->x,capture_piece->PieceSquare->y) &&
       *capture_piece->m_player != *m_player)
        return true;
    return false;
}

bool King::isValidPath(int finalX,int finalY)
{
    if ( (abs(finalX-PieceSquare->x) == 1 && abs(finalY-PieceSquare->y) == 1)
        || (abs(finalX-PieceSquare->x) == 1 && finalY-PieceSquare->y == 0)
        || (abs(finalY-PieceSquare->y) == 1 && finalX-PieceSquare->x == 0) )
        return true;
    return false;
}
void King::drawPath(int finalX,int finalY)
{
    path.resize(2);
    path[0].resize(0);
    path[1].resize(0);
}
