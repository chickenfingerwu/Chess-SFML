#include "Pawn.h"
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "Game.h"
#include "Board.h"
Pawn::Pawn(Player* player,Square* square):Piece(player,square)
{
    m_type = PAWN;
}
Pawn::~Pawn(){
}
bool Pawn::canCapture(Piece* capture_piece){
    if(m_player->color == BLACK){
        if(capture_piece->PieceSquare->x - PieceSquare->x < 0)
            return false;
    }
    else{
        if(capture_piece->PieceSquare->x - PieceSquare->x > 0)
            return false;
    }
    if(*capture_piece->m_player != *m_player){
        if(abs(capture_piece->PieceSquare->x - PieceSquare->x) == 1 && abs(capture_piece->PieceSquare->y - PieceSquare->y) == 1){
            firstStride = false;
            return true;
        }
    }
    return false;
}

bool Pawn::isValidPath(int finalX,int finalY)
{
    if(firstStride){
        if((abs(finalX-PieceSquare->x) == 1 || abs(finalX-PieceSquare->x) == 2) && abs(finalY-PieceSquare->y) == 0){
            firstStride = false;
            return true;
        }
        return false;
    }
    if(abs(finalX-PieceSquare->x) != 1 || abs(finalY-PieceSquare->y) != 0){
        return false;
    }
    int x_dir = (m_player->color == BLACK) ? 1:-1;
    int x_diff = x_dir*(abs(finalX-PieceSquare->x));
    if((finalX-PieceSquare->x == x_diff) && (finalY-PieceSquare->y == 0))
        return true;
    return false;
}
void Pawn::drawPath(int finalX,int finalY)
{
    path.resize(2);
    path[0].resize(0);
    path[1].resize(0);
}
