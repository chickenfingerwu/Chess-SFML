#include "Bishop.h"
#include <stdlib.h>
#include "Player.h"
#include "Game.h"
#include "Board.h"
Bishop::Bishop(Player* player,Square* square):Piece(player,square)
{
    m_type = BISHOP;
}

Bishop::~Bishop(){
}

bool Bishop::canCapture(Piece* capture_piece){
    if(isValidPath(capture_piece->PieceSquare->x,capture_piece->PieceSquare->y) &&
       *capture_piece->m_player != *m_player)
        return true;
    return false;
}

bool Bishop::isValidPath(int finalX,int finalY)
{
    return (abs(finalX - PieceSquare->x) == abs(finalY - PieceSquare->y));
}

void Bishop::drawPath(int finalX,int finalY)
{
    int x_dir = 0;
    int y_dir = 0;
    if((finalX-PieceSquare->x) < 0)
        x_dir = -1;
    else if((finalX-PieceSquare->x) > 0)
        x_dir = 1;
    if((finalY-PieceSquare->y) < 0)
        y_dir = -1;
    else if((finalY-PieceSquare->y) > 0)
        y_dir = 1;
    path[0].resize(abs(finalX-PieceSquare->x));
    path[1].resize(abs(finalX-PieceSquare->x));
    int beginX = PieceSquare->x;
    int beginY = PieceSquare->y;
    for(int i=0;i<path[0].size();i++){
        beginX+=x_dir;
        path[0][i] = beginX;
        beginY+=y_dir;
        path[1][i] = beginY;
    }
}
