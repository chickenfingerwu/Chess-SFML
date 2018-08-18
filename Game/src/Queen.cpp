#include "Queen.h"
#include "Player.h"
#include "Game.h"
#include "Board.h"
Queen::Queen(Player* player,Square* square):Piece(player,square)
{
    m_type = QUEEN;
}

Queen::~Queen(){
}

bool Queen::canCapture(Piece* capture_piece){
    if(isValidPath(capture_piece->PieceSquare->x,capture_piece->PieceSquare->y) &&
       *capture_piece->m_player != *m_player)
        return true;
    return false;
}

bool Queen::isValidPath(int finalX,int finalY)
{
    int x_diff = abs(finalX - PieceSquare->x);
    int y_diff = abs(finalY - PieceSquare->y);
    if((x_diff == 0 && y_diff!=0) || (y_diff == 0 && x_diff!=0)
       || (x_diff == y_diff))
        return true;
    return false;
}
void Queen::drawPath(int finalX,int finalY)
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
    path.resize(2);
    int diff = (abs(finalX-PieceSquare->x) == 0) ? abs(finalY-PieceSquare->y):abs(finalX-PieceSquare->x);
    path[0].resize(diff);
    path[1].resize(diff);
    int beginX = PieceSquare->x;
    int beginY = PieceSquare->y;
    for(int i=0;i<path[0].size();i++){
        beginX+=x_dir;
        path[0][i] = beginX;
        beginY+=y_dir;
        path[1][i] = beginY;
    }
}
