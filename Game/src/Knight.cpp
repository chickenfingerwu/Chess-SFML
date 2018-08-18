#include "Knight.h"
#include "Player.h"
#include <stdlib.h>
#include "Game.h"
#include "Board.h"
#include <iostream>
Knight::Knight(Player* player,Square* square):Piece(player,square)
{
    m_type = KNIGHT;
}
bool Knight::isValidPath(int finalX,int finalY)
{
    int x_diff = abs(finalX - PieceSquare->x);
    int y_diff = abs(finalY - PieceSquare->y);
    if((x_diff == 1 && y_diff == 2) || (x_diff == 2 && y_diff == 1))
        return true;
    return false;
}

bool Knight::canCapture(Piece* capture_piece){
    if(isValidPath(capture_piece->PieceSquare->x,capture_piece->PieceSquare->y) &&
       *capture_piece->m_player != *m_player)
        return true;
    return false;
}

void Knight::drawPath(int finalX,int finalY)
{
    path.resize(2);
    path[0].resize(0);
    path[1].resize(0);
}

Knight::~Knight(){
}
